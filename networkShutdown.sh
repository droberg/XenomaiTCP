#!/bin/bash
# Regular linux is 192.168.11.2 on eth2
sudo ip addr del 192.168.11.2/24 dev eth2
# RTNet is 192.168.11.1 on rteth0
sudo rtifconfig rteth0 down
sudo rmmod rtcap
sudo rmmod rtudp
sudo rmmod rttcp
sudo rmmod rtipv4
sudo rmmod rtpacket
# Assume that rtnet drivers were already loaded at start
# sudo rmmod rt_igb rtnet
