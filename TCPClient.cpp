#include <unistd.h>      // unix standard library
#include <arpa/inet.h>   // IP addresses manipulation utilities
#include <netinet/in.h>  // sockaddr_in structure definition
#include <sys/socket.h>  // berkley socket library
#include <stdio.h>       // standard I/O library
#include <string.h>      // include to have memset
#include <stdlib.h>      // include to have exit

#define MAXLINE 1024

#define PORT     ( 1000 )

// Use define __COBALT to check if we are compiled for Xenomai or regular Linux
#ifndef __COBALT
// Because we explicitly use __COBALT to weed out any bugs or missing syscalls __COBALT needs to be defined
// for regular linux
#define __COBALT
#endif

int main(int argc, char *argv[])
{
    int sock_fd;
    int nread;
    struct sockaddr_in serv_add;
    char buffer[MAXLINE];
    
    // Create socket for client
    sock_fd = __COBALT(socket(AF_INET, SOCK_STREAM, 0));

    // Initialize server address
    memset(&serv_add, 0, sizeof(serv_add));        // Initialize structure
    serv_add.sin_family = AF_INET;                 // Use IPV4
    serv_add.sin_port = htons(PORT);               // Use an unprivileged port

    // Using inet_pton to convert address 
    if(inet_pton(AF_INET, argv[1], &serv_add.sin_addr) < 0)
      perror("Error converting address");

    // Connect to the server
    if ( __COBALT(connect(sock_fd, (struct sockaddr *)&serv_add, sizeof(serv_add) )) < 0)
      perror("Error connecting");

    // Read daytime from server
    while ((nread = __COBALT(read(sock_fd, buffer, MAXLINE))) > 0)
    {
        buffer[nread] = 0;
        if (fputs(buffer, stdout) == EOF)
        {
            perror("fputs error"); // Write response to stdout
            return -1;
        }
    }
    if(nread < 0)
    {
      perror("Could not read");
    }

    close(sock_fd);
    exit(0);
}
