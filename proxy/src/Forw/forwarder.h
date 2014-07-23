/*
 * forwarder.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef FORWARDER_H_
#define FORWARDER_H_

#include "packet.h"
#include "router.h"

namespace std {

class forwarder {
public:
	forwarder();
	virtual ~forwarder();

	void dispatch(packet *p, router *r);
	void route(packet *p, router *r);
	void forward(packet *p);
	void desencapsulate(packet *p);
	void send(packet *p);

	int dgram, raw;
	struct sockaddr_in ProxyAddr;
};

} /* namespace std */
#endif /* FORWARDER_H_ */

