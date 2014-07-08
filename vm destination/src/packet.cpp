/*
 * packet.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#include "packet.h"

namespace std {

packet::packet() {
	lenght = 0;
	originaliphdr = NULL;
	pnchdr = NULL;
}

packet::~packet() {
	// TODO Auto-generated destructor stub
}

struct panaceahdr * packet::panacea_header() {
	pnchdr = (panaceahdr *) msg;
	return pnchdr;
}

struct iphdr * packet::original_ip_header() {
	originaliphdr = (iphdr *) (msg + sizeof(panaceahdr));
	return originaliphdr;
}

void packet::to_string() {
	int j = 1;
	for (unsigned int i = 0; i < lenght; i++) {
		if ((j % 17) == 0) {
			j = 1;
			printf("\n");
		}
		if (msg[i] <= 15)
			printf(" 0%1X ", msg[i]);
		else
			printf(" %1X ", msg[i]);
		j++;
	}
	cout << endl << endl;
}
} /* namespace std */

