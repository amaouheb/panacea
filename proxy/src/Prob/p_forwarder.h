/*
 * p_forwarder.h
 *
 *  Created on: 6 juin 2014
 *      Author: Anouar
 */

#ifndef P_FORWARDER_H_
#define P_FORWARDER_H_

#include "p_packet.h"
#include "p_agent.h"

namespace std {

class p_forwarder {
public:
	p_forwarder();
	virtual ~p_forwarder();
	// La fonction la plus importante pour le transfert des paquets probes
	void process(p_packet *p, p_agent *a);

	/*
	 * Socket pour l'envoi des paquets probes en transit
	 */
	int socketDescription;
	struct sockaddr_in proxyAddr;
};

}
#endif /* PROBE_FORWARDER_H_ */
