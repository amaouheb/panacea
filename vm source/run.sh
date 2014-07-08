#!/bin/sh
# Install and run script for vm
#

OSNAME=`uname -s`

start_panacea() {
    g++ -Wall -o exe/vmprog src/vmprog.cpp  -lnfnetlink -lnetfilter_queue
    exe/vmprog
}

ee() {
    echo $*
    eval $*
}

linux_set_iptables() {
    echo Adding netfilter iptales rule...

    {
        while read line
   	do
	   i=2
	   l=`echo $line| cut -d',' -f $i`
	   if [ "$line" != "" ]
	   then

	   while [ "$l" != "" ]
	   do
	        ee iptables -A OUTPUT -j NFQUEUE -d $l
	        i=`expr $i + 1`
	        l=`echo $line| cut -d',' -f $i`
	   done
	   fi

	done

     } < exe/resolution

}

linux_unset_iptables() {
    echo Removing netfilter iptables rules...
    iptables --flush
    exit
}



check_root() {
    if [ `whoami` != "root" ]
    then
        echo "must be root"
        exit 1
    fi
}

check_ssh() {
    if [ -n "$SSH_CONNECTION" ]
    then
        read -p 'Command may disrupt existing ssh connections. Proceed? [y/N] ' C
        if [ "$C" != "y" ]
        then
            exit 1
        fi
    fi
}

check_lib() {

    ldconfig -p | grep libnetfilter_queue.so > /dev/null
    if [ $? -eq 0 ]
    then
    	echo "Library libnetfilter_queue : OK"
    else
	echo "Instaling libnetfilter_queue ..."
	apt-get install libnetfilter-queue-dev
    fi

    ldconfig -p | grep nfnetlink.so > /dev/null
    if [ $? -eq 0 ]
    then
    	echo "Library nfnetlink : OK"
    else
	echo "Instaling nfnetlink..."
	apt-get install libnfnetlink-dev
    fi

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


    echo "Cheking all installation..."
    ldconfig -p | grep libnetfilter_queue.so > /dev/null
    is=$?
    ldconfig -p | grep nfnetlink.so > /dev/null
    is=`expr $is + $?`
    g++ --version | grep 4.8 > /dev/null
    is=`expr $is + $?`

    if [ $is != 0 ]
    then
	echo "There was an error while installing a library!!"
	exit 1
    fi

}

check_topologie(){

echo Fitching my proxy addr...
myipaddr=$(ifconfig | grep 'inet ad' | grep -v '127.0.0.1' | cut -d: -f2 | awk '{ print $1}' | head -1)

found="0"
    while read line
    do
	if [ "$found" = "1" ]
	then
	break
	fi

	s=`echo $line| cut -d' ' -f 1`
	if [ "$s" = "px" ]
	then
		pxadd=`echo $line| cut -d' ' -f 3`
		read line
		while [ "$line" != "" ]
		do
		   	s=`echo $line| cut -d' ' -f 5`
			ss=`echo $line| cut -d' ' -f 3`
			if [ "$s" = "$myipaddr" ] 
			then
			echo $pxadd > exe/proxy
			echo $ss > exe/myip
			found="1"
			break
			fi
			read line
		done
	fi
    done < topologie/topologie.conf

    echo Fitching panacea noeud...
    echo -n "" > exe/resolution
    while read line
    do
	l=`echo $line| cut -d' ' -f 1`
	if [ "$l" = "px" ]
	then
	   ll=`echo $line| cut -d' ' -f 3`
	   if [ "$ll" != "$pxadd" ]
	   then
	   	echo -n $ll"," >> exe/resolution
		read line
		while [ "$line" != "" ]
		do
			s=`echo $line| cut -d' ' -f 3`
			echo -n $s"," >> exe/resolution
			read line
		done
		echo "" >> exe/resolution
	   fi
	fi
    done < topologie/topologie.conf
}


case "$OSNAME" in
    Linux)
        check_root
	check_lib
	check_topologie
        linux_set_iptables
        trap linux_unset_iptables 2 # trap SIGINT to remove iptables rules before exit
        start_panacea
        linux_unset_iptables
        ;;
    FreeBSD|Darwin)
      
        ;;
    [Cc][Yy][Gg][Ww][Ii][Nn]*)
        
        ;;
esac
