#include <sys/types.h>   // predefined types
#include <unistd.h>      // unix standard library
#include <arpa/inet.h>   // IP addresses conversion utilities
#include <netinet/in.h>  // sockaddr_in structure definition
#include <sys/socket.h>  // berkley socket library
#include <stdio.h>       // standard I/O library
#include <string.h>      // include to have memset
#include <stdlib.h>      // include to have exit
#include <time.h>        // time manipulation primitives 
 
#define MAXLINE  (   80 )
#define BACKLOG  (   10 )
#define PORT     ( 1000 )

// Use define __COBALT to check if we are compiled for Xenomai or regular Linux
#ifndef __COBALT
// Because we explicitly use __COBALT to weed out any bugs or missing syscalls __COBALT needs to be defined
// for regular linux
#define __COBALT
#else
// Define __XENOMAI_RT__ if we are compiling for Xenomai
#define __XENOMAI_RT__
#endif

// Function for creating, initalizing, and binding a socket
// Returns the socket or -1
int createListenSocket()
{
  int list_fd;  
  struct sockaddr_in serv_add; 
  // Create listen socket 
  list_fd = __COBALT(socket(AF_INET, SOCK_STREAM, 0));
         
  // Initialize server address
  memset(&serv_add, 0, sizeof(serv_add));        // Initialize structure
  serv_add.sin_family = AF_INET;                 // Use IPV4
  serv_add.sin_port = htons(PORT);               // Use an unprivileged port
  serv_add.sin_addr.s_addr = htonl(INADDR_ANY);  // Allow connections from anywhere
     
  // Bind socket to server address
  if(__COBALT(bind(list_fd, (struct sockaddr *)&serv_add, sizeof(serv_add))) < 0)
    {
      perror("Error binding");
      return -1;
    }
        
  // Mark socket as a listening socket
  if(listen(list_fd, BACKLOG) < 0)
    {
      perror("Error listening");
      return -1;
    }
  return list_fd;
}

int main(int argc, char *argv[]) 
{
  int list_fd, conn_fd;  
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  char buffer[MAXLINE]; 
  time_t timeval; 

  // For regular linux, the listen socket should be created once, here
#ifndef __XENOMAI_RT__
  list_fd = createListenSocket(); // Create listen socket
#endif  
  while (true) 
    {
#ifdef __XENOMAI_RT__
      list_fd = createListenSocket(); // Create listen socket
#endif  

#ifdef __USE_SELECT__      
      // Set up structure for select
      fd_set in_fds;
      FD_ZERO(&in_fds);
      FD_SET(list_fd, &in_fds);
      // We could have a timeout on select but this was disabled to simplify the example
      // struct timeval tv = { .tv_sec = 1, .tv_usec = 0};

      int selRet = __COBALT(select(list_fd + 1, &in_fds, 0, 0, 0));
      printf("Select returned  = %i\n", selRet);	
      if(FD_ISSET(list_fd, &in_fds))
	printf("The used list_fd socket (%i) is in FDSET\n", list_fd);	
#endif
      // Accept the connection and print info in the socket
      // Note: It appears that &client_addr and &client_len cannot be nullptrs here.
      client_len = sizeof(client_addr);
      if((conn_fd = __COBALT(accept(list_fd, (struct sockaddr *) &client_addr, &client_len))) < 0)
	{
	  perror("Accept failed ");
	  return -1;
	}
      printf("The client address is: %s\n",inet_ntoa(client_addr.sin_addr));
      printf("The file descriptors for the sockets are: conn_fd = %i, list_fd = %i\n", conn_fd, list_fd);

      // Prepare return values
      timeval = time(NULL); 
      snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&timeval)); 
      
      __COBALT(write(conn_fd, buffer, strlen(buffer))); // Write daytime to the client
      __COBALT(close(conn_fd)); // For Xenomai this is the same socket-fd as the listening
                                // socket so it needs to be recreated in the next iteration
    } 
#ifndef __XENOMAI_RT__
  __COBALT(close(list_fd));
#endif  
    
  exit(0); 
}
