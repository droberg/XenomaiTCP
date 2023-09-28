#!/bin/bash
# Assume that rtnet drivers were already loaded at start
# sudo modprobe rtnet
# sudo modprobe rt_igb
sudo modprobe rtipv4
sudo modprobe rttcp
sudo modprobe rtudp
sudo modprobe rtcap
sudo modprobe rtpacket
# Regular linux is 192.168.11.2 on eth2
sudo ip addr add 192.168.11.2/24 dev eth2
# RTNet is 192.168.11.1 on rteth0
sudo rtifconfig rteth0 up 192.168.11.1 netmask 255.255.255.0 -promisc
