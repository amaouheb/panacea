/*
 * d_forwarder.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#include "d_forwarder.h"

namespace std {

d_forwarder::d_forwarder() {

	/*
	 * Créer l'interface réseau pour l'envoi des paquets data en transit et
	 * initialiser les variables statiques de l'addresse destination
	 * (AF_INET, DATA_PORT)
	 *
	 */
	dgram = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (dgram == -1) {
		cout << "Error creating UDP socket\n";
		exit(1);
	}

	bzero(&ProxyAddr, sizeof(ProxyAddr));
	ProxyAddr.sin_family = AF_INET;
	ProxyAddr.sin_port = htons(DATA_PORT);
}

void d_forwarder::dispatch(d_packet * p, router *r) {

	p->pnchdr = p->panacea_header();

	/* Selon la valeur du nextHop nous allons soit router le paquet,
	 * le transferer, ou le des encapsuler.
	 */

	if (p->pnchdr->nextHop == 0)
		route(p, r);

	if ((p->pnchdr->nextHop - 1) == p->pnchdr->pathLen)
		desencapsulate(p);
	else {
		forward(p);
	}
}

void d_forwarder::route(d_packet * p, router *r) {

	cout << "route" << endl;
	r->lookupforpath(p);
	p->to_string();
}

void d_forwarder::forward(d_packet * p) {

	cout << "forward" << endl;
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

/*
 * Maintenant avec la question du NAT cette fonction envoie le paquet vers
 * la vm SANS le desencapsuler.
 *
 */

void d_forwarder::desencapsulate(d_packet * p) {

	cout << "desencapsulate" << endl;
	p->originaliphdr = p->original_ip_header();
	cout << p->originaliphdr->daddr << endl;

	ProxyAddr.sin_addr.s_addr = p->originaliphdr->daddr;
	p->pnchdr->nextHop++;
	p->to_string();

	if (sendto(dgram, (char*) p->msg, p->lenght, 0,
			(struct sockaddr*) &ProxyAddr, sizeof(sockaddr_in)) < 0) {
		cerr << "sendto() failed fd here" << endl;
	} else {
		cout << "sent" << endl;
	}
}

d_forwarder::~d_forwarder() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
