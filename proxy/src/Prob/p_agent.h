/*
 * p_agent.h
 *
 *  Created on: 28 mai 2014
 *      Author: Anouar
 */

#ifndef P_AGENT_H_
#define P_AGENT_H_

#include "p_packet.h"
#include "../Forw/router.h"
#include "../Forw/path.h"

namespace std {

class p_agent {
public:
	p_agent(router *r);
	virtual ~p_agent();
	void execute();
	void result(p_packet *p);

	int probSender;
	struct sockaddr_in add;
	p_packet p;

	// all hops ONLY
	std::vector<unsigned long> index_hops;
	// all destinations ONLY
	std::vector<unsigned long> index_destinations;
	// my IP
	string myIp;
	// result ONLY
	std::map<string, long> resulTable;

};

} /* namespace std */
#endif /* P_AGENT_H_ */
