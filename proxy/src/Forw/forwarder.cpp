/*
 * Dispatcher.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#include "forwarder.h"

namespace std {

forwarder::forwarder() {

	// RAW SOCKET
	raw = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (raw == -1) {
		cout << "Error creating RAW socket\n";
		exit(1);
	}

	const int on = 1;
	if (setsockopt(raw, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
		cerr << "setsockopt() failed to set IP_HDRINCL fd" << endl;
	}

// DGRAM SOCKET
	dgram = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (dgram == -1) {
		cout << "Error creating UDP socket\n";
		exit(1);
	}
}

void forwarder::desencapsulate(packet * p) {
	cout << "desencapsulate" << endl;

	p->originaliphdr = p->original_ip_header();
	int res = htons(p->originaliphdr->tot_len);

	bzero(&ProxyAddr, sizeof(ProxyAddr));
	ProxyAddr.sin_family = AF_INET;
	cout << p->originaliphdr->daddr << endl;
	ProxyAddr.sin_addr.s_addr = p->originaliphdr->daddr;

	memcpy(p->msg, p->msg + sizeof(panaceahdr), res);
	p->lenght = res;

	p->to_string();
	if (sendto(raw, (char*) p->msg, p->lenght, 0, (struct sockaddr*) &ProxyAddr,
			sizeof(sockaddr_in)) < 0) {
		cerr << "sendto() failed fd" << endl;
	} else {
		cout << "sent" << endl;
	}
}

void forwarder::forward(packet * p) {
	cout << "forward" << endl;

	bzero(&ProxyAddr, sizeof(ProxyAddr));
	ProxyAddr.sin_family = AF_INET;
	ProxyAddr.sin_port = htons(DATA_PORT);
	ProxyAddr.sin_addr.s_addr = p->pnchdr->path[p->pnchdr->nextHop - 1];
	p->pnchdr->nextHop++;
	p->to_string();

	if (sendto(dgram, (char*) p->msg, p->lenght, 0,
			(struct sockaddr*) &ProxyAddr, sizeof(sockaddr_in)) < 0) {
		cerr << "sendto() failed fd here" << endl;
	} else {
		cout << "sent" << endl;
	}
}

void forwarder::route(packet * p, router *r) {
	cout << "route" << endl;
	r->lookupforpath(p);
	p->to_string();
}

void forwarder::dispatch(packet * p, router *r) {

	p->pnchdr = p->panacea_header();
	cout << p->pnchdr->nextHop << endl;

	if (p->pnchdr->nextHop == 0)
		route(p, r);

	// TODO change this to ==
	if ((p->pnchdr->nextHop - 1) == p->pnchdr->pathLen)
		desencapsulate(p);
	else {
		forward(p);
	}
}

forwarder::~forwarder() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

