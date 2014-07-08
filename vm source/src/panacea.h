/*
 * panacea.h
 *
 *  Created on: Jun 8, 2014
 *      Author: Anouar
 */

#ifndef PANACEA_H_
#define PANACEA_H_

#include <sys/types.h>
#include <sys/socket.h>		// socket
#include <netinet/ip.h>		// ipheader
#include <string.h>			// memcpy
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

extern "C" {
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
}

#define MAX_LENGHT_PARAM 4
#define DATA_PORT 9548
#define BUFLENGHT 4096

struct panaceahdr {
	uint32_t pxDest;
	uint32_t vmSrc;
	uint32_t hops[MAX_LENGHT_PARAM];
	unsigned int nbrHops :4;
	unsigned int nextHop :4;
};

#endif /* PANACEA_H_ */

