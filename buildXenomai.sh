#!/bin/bash
# Generated commands to build example, obtained from cmake setup
# --------------------------------
# > xeno-config --cflags --posix
# -I/usr/xenomai/include/cobalt -I/usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -fasynchronous-unwind-tables -D__COBALT__ -D__COBALT_WRAP__
# --------------------------------
# > xeno-config --ldflags --posix
# -Wl,--no-as-needed -Wl,@/usr/xenomai/lib64/cobalt.wrappers -Wl,@/usr/xenomai/lib64/modechk.wrappers /usr/xenomai/lib64/xenomai/bootstrap.o -Wl,--wrap=main -Wl,--dynamic-list=/usr/xenomai/lib64/dynlist.ld -L/usr/xenomai/lib64 -lcobalt -lmodechk -lpthread -lrt

# Compile server
/usr/bin/c++  -I/usr/xenomai/include/cobalt -I/usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -fasynchronous-unwind-tables -D__COBALT__ -D__COBALT_WRAP__ -g -Wall -MD -MT TCPServer.cpp.o -MF TCPServer.cpp.o.d -o TCPServer.cpp.o -c TCPServer.cpp
# Link server
/usr/bin/c++ -Wl,--no-as-needed -Wl,@/usr/xenomai/lib64/cobalt.wrappers -Wl,@/usr/xenomai/lib64/modechk.wrappers /usr/xenomai/lib64/xenomai/bootstrap.o -Wl,--wrap=main -Wl,--dynamic-list=/usr/xenomai/lib64/dynlist.ld -rdynamic TCPServer.cpp.o -o TCPServer_Xeno -L/usr/xenomai/lib64 -lcobalt -lmodechk -lpthread -lrt

# Compile client
/usr/bin/c++ -I/usr/xenomai/include/cobalt -I/usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -fasynchronous-unwind-tables -D__COBALT__ -D__COBALT_WRAP__ -g -Wall -MD -MT TCPClient.cpp.o -MF TCPClient.cpp.o.d -o TCPClient.cpp.o -c TCPClient.cpp
# Link client
/usr/bin/c++ -Wl,--no-as-needed -Wl,@/usr/xenomai/lib64/cobalt.wrappers -Wl,@/usr/xenomai/lib64/modechk.wrappers /usr/xenomai/lib64/xenomai/bootstrap.o -Wl,--wrap=main -Wl,--dynamic-list=/usr/xenomai/lib64/dynlist.ld -rdynamic TCPClient.cpp.o -o TCPClient_Xeno -L/usr/xenomai/lib64 -lcobalt -lmodechk -lpthread -lrt



