/*
 * packet.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#include "d_packet.h"

namespace std {

d_packet::d_packet() {
	lenght = 0;
	originaliphdr = NULL;
	pnchdr = NULL;
}

/*
 * Le load du paquet de data est definie par les deux structures, ip et
 * probhdr. L'attribut probeheader pointera donc sur le debut du message et
 * l'attribut originaliphdr pointera sur le debut du paquet original
 *
 */
struct panaceahdr * d_packet::panacea_header() {
	pnchdr = (panaceahdr *) msg;
	return pnchdr;
}

struct iphdr * d_packet::original_ip_header() {
	originaliphdr = (iphdr *) (msg + sizeof(panaceahdr));
	return originaliphdr;
}

/*
 * Methode pour l'affichage du contenu du message. Le format utilisé
 * est le même qu'affiche wireshark (par eg.)
 *
 */

void d_packet::to_string() {
	int j = 1;
	for (unsigned int i = 0; i < lenght; i++) {
		if ((j % 17) == 0) {
			j = 1;
			printf("\n");
		}
		if (j % 2 == 0)
			printf(" ");

		if (msg[i] <= 15)
			printf(" 0%1X ", msg[i]);
		else
			printf(" %1X ", msg[i]);
		j++;
	}
	cout << endl << endl;
}

d_packet::~d_packet() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
