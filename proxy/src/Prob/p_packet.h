/*
 * p_packet.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef P_PACKET_H_
#define P_PACKET_H_

#include "../panacea.h"

namespace std {

class p_packet {

public:
	p_packet();
	virtual ~p_packet();
	// Méthode pour l'initialisation du pointeur probeheader
	struct probehdr * probe_header();
	// Méthode pour l'affichage du contenu du msg
	void to_string();

<<<<<<< HEAD
	/*
	 * Tableau de taille 4096 qui va contenir le message (niveau transport).
	 * Longueur du message à envoyer.
	 * Pointeur vers la structure probhdr.
	 *
	 */
=======
	// Tableau de taille 4096 qui va contenir le message (pas d'entête réseau ni transport)
>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
	unsigned char msg[BUFLENGHT];
	// Longueur du message à envoyer
	unsigned lenght;
	// Pointeur vers la structure probhdr
	struct probehdr *probeheader;
};

}
#endif /* P_PACKET_H_ */
