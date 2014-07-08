/*
 * d_forwarder.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef D_FORWARDER_H_
#define D_FORWARDER_H_

#include "d_packet.h"
#include "../router.h"

namespace std {

class d_forwarder {
public:
	d_forwarder();
	virtual ~d_forwarder();
	// La fonction la plus importante pour le transfert et le routage datas
	void dispatch(d_packet *p, router *r);
	void route(d_packet *p, router *r);
	void forward(d_packet *p);
	void desencapsulate(d_packet *p);
	//void send(d_packet *p);

	/*
	 * Socket pour l'envoi des paquets probes en transit
	 */
	int dgram;
	struct sockaddr_in ProxyAddr;
};

}
#endif /* D_FORWARDER_H_ */
