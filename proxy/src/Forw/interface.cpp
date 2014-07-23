/*
 * agent.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#include "interface.h"

namespace std {

router *rrr;

interface::interface(router *r) {
	rrr = r;
	// reciever socket
	sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd == -1) {
		cout << "Error creating raw socket\n";
		exit(1);
	}

	bzero(&proxy, sizeof(proxy));
	proxy.sin_family = AF_INET;
	proxy.sin_port = htons(DATA_PORT);
	proxy.sin_addr.s_addr = htonl(INADDR_ANY );

	int err = bind(sd, (struct sockaddr *) &proxy, sizeof(sockaddr));
	if (err < 0) {
		cout << "Error binding socket" << err << endl;
		exit(1);
	}
	slen = sizeof(vm);
}

void interface::process() {
	p.lenght = recvfrom(sd, p.msg, sizeof(packet) - 1, 0,
			(struct sockaddr *) &vm, &slen);
	p.to_string();
	f.dispatch(&p, rrr);
}

interface::~interface() {

}

} /* namespace std */

