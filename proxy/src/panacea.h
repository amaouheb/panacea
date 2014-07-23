/*
 * panacea.h
 *
 *  Created on: 24 avr. 2014
 *      Author: Anouar
 */

#ifndef PANACEA_H_
#define PANACEA_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#define DATA_PORT 9548
#define DATA_MAX_PATH_LENGHT 4 // au pire je vais faire 4 sauts
#define BUFLENGHT 4096

struct panaceahdr {
	uint32_t pxDdest;
	uint32_t path[DATA_MAX_PATH_LENGHT];
	unsigned int pathLen :4;
	unsigned int nextHop :4;
};

#define PROBE_PORT 9547
#define PROBE_MAX_PATH_LENGHT 4 // au pire de vais mesurer une chemin de longeur 4
#define BUFLENGHT 4096

/*
 *  [nextStamp][nextHop][pathLen][direction][path]
 */
struct probehdr {
	unsigned int nextHop :4;
	unsigned int nextStamp :4;
	unsigned int direction :4; // allee ou retour
	unsigned int pathLen :4;
	unsigned int path[PROBE_MAX_PATH_LENGHT + 1]; // +1 pour l'adresse de la source
	struct timeval dates[(2 * (PROBE_MAX_PATH_LENGHT + 1)) - 1];
};

#endif /* PANACEA_H_ */
