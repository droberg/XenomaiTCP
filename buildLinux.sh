#!/bin/bash

# Compile server
/usr/bin/c++  -o TCPServer.cpp.o -c TCPServer.cpp
# Link server
/usr/bin/c++ TCPServer.cpp.o -o TCPServer_Linux


# Compile client
/usr/bin/c++  -o TCPClient.cpp.o -c TCPClient.cpp
# Link client
/usr/bin/c++ TCPClient.cpp.o -o TCPClient_Linux



