/*
 * d_interface.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef D_INTERFACE_H_
#define D_INTERFACE_H_

#include "d_packet.h"
#include "d_forwarder.h"

namespace std {

class d_interface {
public:

	d_interface(router *r);
	virtual ~d_interface();
	void process();

	/*
	 * Socket pour l'écoute et la réception des paquets datas
	 */
	int sd;
	struct sockaddr_in proxy, vm;
	socklen_t slen;

	// Variable pour garder le paquet reçu
	d_packet p;
	// forwarder des paquets datas
	d_forwarder f;
	// Réference vers la table de routage.
	router *myRouter;
};

}
#endif /* DATA_INTERFACE_H_ */
