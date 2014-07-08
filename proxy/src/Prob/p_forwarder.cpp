/*
 * p_forwarder.cpp
 *
 *  Created on: 6 juin 2014
 *      Author: Anouar
 */

#include "p_forwarder.h"

namespace std {

// Variable temporaire
struct timeval stamp;

p_forwarder::p_forwarder() {

	/*
	 * Créer l'interface réseau pour l'envoi des paquets probe en transit et
	 * initialiser les variables statiques de l'addresse destination
	 * (AF_INET, PROBE_PORT)
	 *
	 */
	socketDescription = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socketDescription == -1) {
		cout << "Error creating UDP socket\n";
		exit(1);
	}

	bzero(&proxyAddr, sizeof(proxyAddr));
	proxyAddr.sin_family = AF_INET;
	proxyAddr.sin_port = htons(PROBE_PORT);
}

void p_forwarder::process(p_packet *p, p_agent *a) {

	// Variable utilisé lors de l'envoi des paquets en transit
	bool reached = false;

	p->probeheader = p->probe_header();
	if (p->probeheader->nextHop < p->probeheader->pathLen) {

		if (p->probeheader->direction == 0) {
			/*
			 * ALLER
			 *
			 */
			p->probeheader->nextHop++;
			proxyAddr.sin_addr.s_addr =
					p->probeheader->path[p->probeheader->nextHop];
			gettimeofday(&stamp, NULL);
			p->probeheader->dates[p->probeheader->nextStamp] = stamp;
			p->probeheader->nextStamp += 2;

		} else {
			/*
			 * RETOUR
			 *
			 */
			if (p->probeheader->nextHop == 0) {

				// Si on a fait le tour , on fait passer le packet a l'agent
				gettimeofday(&stamp, NULL);
				p->probeheader->dates[p->probeheader->nextStamp] = stamp;
				a->result(p);
				reached = true;

			} else {
				// Sinon continue a reculer
				p->probeheader->nextHop--;
				proxyAddr.sin_addr.s_addr =
						p->probeheader->path[p->probeheader->nextHop];
				gettimeofday(&stamp, NULL);
				p->probeheader->dates[p->probeheader->nextStamp] = stamp;
				p->probeheader->nextStamp -= 2;
			}
		}

	} else {
		// On arrive au dérnier noeud du chemin: On doit faire un demi tour
		p->probeheader->direction = 1;
		p->probeheader->nextHop--;
		proxyAddr.sin_addr.s_addr =
				p->probeheader->path[p->probeheader->nextHop];

		gettimeofday(&stamp, NULL);
		p->probeheader->dates[p->probeheader->nextStamp] = stamp;
		p->probeheader->nextStamp--;
	}

	if (!reached) {
		p->to_string();
		if (sendto(socketDescription, (char*) p->msg, p->lenght, 0,
				(struct sockaddr*) &proxyAddr, sizeof(sockaddr_in)) < 0) {
			cerr << "sendto() failed fd here" << endl;
		} else {
			cout << "sent" << endl;
		}
	}
}

p_forwarder::~p_forwarder() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
