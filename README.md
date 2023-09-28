# XenomaiTCP
Repository for illustating how to implement a TCP Client and Server in  Xenomai Linux

The code was inspired by:
https://riptutorial.com/posix/example/17612/tcp-daytime-client

## Preparation
The example assumes that you have successfully setup a xenomai installation in /usr/xenomai and compiled a Xenomai enabled kernel with support for rtnet and ethernet drivers. 

This example has been tested using 
* Xenomai-3.2.4 
* linux-dovetail 5.10.191

## Usage
* Compile the code using e.g. the example build-scripts for Xenomai/Linux. The build-scripts are used to show exactly what flags were used for the test (using the xeno-config on the specific target)
* Set up the network such that there is one real time adater and one regular adapter. An example script "networkSetup.sh" is provided to show what modules are required. Note that this script assumes that
  * The regular linux network card is called *eth2*
  * The Xenomai RTNet network is called *rteth0*
  * The Network cards are connected so that it is possible to direct traffic in between them.
* Execute the following commands in the build directory, using different terminals
  * > sudo ./TCPServer_Xenomai
  * > ./TCPClient_Linux 192.168.xx.yy (where xx.yy is the IP of the real time ethernet card )
    
