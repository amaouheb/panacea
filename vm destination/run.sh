#!/bin/sh
# Install and run script for vm
#

OSNAME=`uname -s`

start_panacea() {
    g++ -Wall -o exe/xMain src/xMain.cpp src/packet.cpp
    exe/xMain
}


case "$OSNAME" in
    Linux)
        start_panacea
        ;;
    FreeBSD|Darwin)
      
        ;;
    [Cc][Yy][Gg][Ww][Ii][Nn]*)
        
        ;;
esac
