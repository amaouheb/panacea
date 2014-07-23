/*
 * interface.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "packet.h"
#include "forwarder.h"

namespace std {

class interface {
public:
	//interface();
	interface(router *r);
	virtual ~interface();
	void process();

	int sd;
	struct sockaddr_in proxy, vm;
	socklen_t slen;

	packet p;
	forwarder f;
};

} /* namespace std */
#endif /* INTERFACE_H_ */
