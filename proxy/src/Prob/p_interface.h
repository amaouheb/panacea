/*
 * p_interface.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef P_INTERFACE_H_
#define P_INTERFACE_H_

#include "p_packet.h"
#include "p_forwarder.h"

namespace std {

class p_interface {
public:

	p_interface(p_agent *a);
	virtual ~p_interface();
	void process();

	/*
	 * Socket pour l'écoute et la réception des paquets probes
	 */
	int socketDescription;
	struct sockaddr_in proxyAddr;
	socklen_t socketLen;

	// Variable pour garder le paquet reçu
	p_packet p;
	// forwarder des paquets probes
	p_forwarder f;
	// Réference vers l'agent de mesure.
	p_agent *myAgent;
};

}
#endif /* PROBE_INTERFACE_H_ */
