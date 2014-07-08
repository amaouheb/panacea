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

/*
<<<<<<< HEAD
 * Le load du paquet de mesure est entierement definie par la structure
 * probhdr, L'attribut probeheader pointera donc sur le debut du message.
 *
=======
 * L'élément probeheader pointe sur le debut du message
>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
 */
struct probehdr * p_packet::probe_header() {
	probeheader = (probehdr *) (msg);
	return probeheader;
}

/*
<<<<<<< HEAD
 * Methode pour l'affichage du contenu du message. Le format utilisé
 * est le même qu'affiche wireshark (par eg.)
 *
=======
 * Methode pour l'affichage du contenu du message
 * les entetes réseau et
>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
 */
void p_packet::to_string() {
	int j = 1;
	for (unsigned int i = 0; i < lenght; i++) {
		if ((j % 17) == 0) {
			j = 1;
			printf("\n");
		}
		if (j % 2 == 0)
			printf(" ");

		if (msg[i] <= 15)
			printf("0%1X ", msg[i]);
		else
			printf("%1X ", msg[i]);

		j++;
	}
	cout << endl << endl;
}

p_packet::~p_packet() {
<<<<<<< HEAD
	// TODO Auto-generated destructor stub
}

=======

}
>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
} /* namespace std */

