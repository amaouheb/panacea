#!/bin/sh
#
# Install and run script for proxy
#

OSNAME=`uname -s`

start_proxy() {
echo Compiling...
g++ -Wall -o exe/xMain src/xMain.cpp src/Forw/interface.cpp src/Forw/forwarder.cpp src/Forw/packet.cpp src/Forw/path.cpp src/Forw/router.cpp src/Prob/p_agent.cpp src/Prob/p_forwarder.cpp src/Prob/p_packet.cpp -pthread -std=c++11
exe/xMain
}

ee() {
    echo $*
    eval $*
}

check_standard() {

    g++ --version | grep 4.8 > /dev/null
    if [ $? -eq 0 ]
    then
    	echo "C++11 standard installed : OK"
    else
	apt-get install python-software-properties
	add-apt-repository ppa:ubuntu-toolchain-r/test
	apt-get update

	echo "Instaling g++"
	apt-get install g++-4.8
	rm /usr/bin/g++
	ln -s /usr/bin/g++-4.8 /usr/bin/g++
       	echo "Instaling cpp"
	apt-get install cpp-4.8
	rm /usr/bin/cpp
	ln -s /usr/bin/cpp-4.8 /usr/bin/cpp
	echo "Instaling gcc"
	apt-get install gcc-4.8
	rm /usr/bin/gcc
	ln -s /usr/bin/gcc-4.8 /usr/bin/gcc
    fi
}

check_topologie(){
echo Fitching panacea routing nodes...
echo -n "" > exe/hops

myipaddr=$(ifconfig | grep 'inet ad' | grep -v '127.0.0.1' | cut -d: -f2 | awk '{ print $1}' | head -1)

dest=$(head -n 1 exe/destinations)
x=0
while read line
do
	l=`echo $line| cut -d' ' -f 1`
	if [ "$l" = "px" ]
	then

	   ll=`echo $line| cut -d' ' -f 3`
	   lll=`echo $line| cut -d' ' -f 5`

	   if [ "$lll" != "$myipaddr" ]
	   then
		if [ "$ll" != "$dest" ]
		then
		if [ "$x" = 1 ]
		then
			echo "" >> exe/hops
		fi
		echo -n  $ll >> exe/hops
		x=1
		fi
	   else
		echo $ll > exe/myip
	   fi
	fi
done < topologie/topologie.conf
}


case "$OSNAME" in
    Linux)
	check_standard
	check_topologie
	start_proxy
        ;;
    FreeBSD|Darwin)
      
        ;;
    [Cc][Yy][Gg][Ww][Ii][Nn]*)
        
        ;;
esac
