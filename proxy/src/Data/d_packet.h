/*
 * d_packet.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef D_PACKET_H_
#define D_PACKET_H_

#include "../panacea.h"

namespace std {

class d_packet {
public:
	d_packet();
	virtual ~d_packet();
	struct panaceahdr * panacea_header();
	struct iphdr * original_ip_header();
	void to_string();

	/*
	 * Tableau de taille 4096 qui va contenir le message (niveau transport).
	 * Longueur du message à envoyer.
	 * Pointeur vers la structure ip du paquet original.
	 * Pointeur vers la structure probhdr.
	 *
	 */

	unsigned char msg[BUFLENGHT];
	unsigned lenght;
	struct iphdr *originaliphdr;
	struct panaceahdr *pnchdr;
};

}
#endif /* D_PACKET_H_ */
