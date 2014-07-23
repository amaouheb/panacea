/*
 * p_packet.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#include "p_packet.h"

namespace std {

p_packet::p_packet() {

	probeheader = NULL;
	lenght = 0;
}

struct probehdr * p_packet::probe_header() {
	probeheader = (probehdr *) (msg);
	return probeheader;
}

p_packet::~p_packet() {
	// TODO Auto-generated destructor stub
}

void p_packet::to_string() {
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

