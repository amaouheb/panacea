/*
 * p_forwarder.h
 *
 *  Created on: 6 juin 2014
 *      Author: root
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
	void process(p_agent *a);

	int receiver, sender;
	struct sockaddr_in addr1, addr2;
	socklen_t slen;

	p_packet p;
};

} /* namespace std */
#endif /* PROBEFORWARDER_H_ */
