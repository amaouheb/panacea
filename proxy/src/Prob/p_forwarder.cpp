/*
 * ProbeForwarder.cpp
 *
 *  Created on: 6 juin 2014
 *      Author: root
 */

#include "p_forwarder.h"

namespace std {

struct timeval stamp;

p_forwarder::p_forwarder() {

	// reciever
	receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (receiver == -1) {
		cout << "Error creating DGRAM socket\n";
		exit(1);
	}

	bzero(&addr1, sizeof(addr1));
	addr1.sin_family = AF_INET;
	addr1.sin_port = htons(PROBE_PORT);
	addr1.sin_addr.s_addr = htonl(INADDR_ANY );

	int err = bind(receiver, (struct sockaddr *) &addr1, sizeof(sockaddr));
	if (err < 0) {
		cout << "Error binding socket" << err << endl;
		exit(1);
	}

	// sender
	sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sender == -1) {
		cout << "Error creating UDP socket\n";
		exit(1);
	}
	slen = sizeof(addr2);
}

void p_forwarder::process(p_agent *a) {

	bool reached = false;
	p.lenght = recvfrom(receiver, p.msg, sizeof(p_packet) - 1, 0,
			(struct sockaddr *) &addr2, &slen);
	p.to_string();
	p.probeheader = p.probe_header();

	bzero(&addr1, sizeof(addr1));
	addr1.sin_family = AF_INET;
	addr1.sin_port = htons(PROBE_PORT);

	if (p.probeheader->nextHop < p.probeheader->pathLen) {

		if (p.probeheader->direction == 0) {
			/*
			 * ALLER
			 *
			 */
			p.probeheader->nextHop++;
			addr1.sin_addr.s_addr = p.probeheader->path[p.probeheader->nextHop];
			gettimeofday(&stamp, NULL);
			p.probeheader->dates[p.probeheader->nextStamp] = stamp;
			p.probeheader->nextStamp += 2;

		} else {
			/*
			 * RETOUR
			 *
			 */
			if (p.probeheader->nextHop == 0) {

				// Si on a fait le tour passe le packet a l'agent
				gettimeofday(&stamp, NULL);
				p.probeheader->dates[p.probeheader->nextStamp] = stamp;
				a->result(&p);
				reached = true;

			} else {
				// Sinon continue a reculer
				p.probeheader->nextHop--;
				addr1.sin_addr.s_addr =
						p.probeheader->path[p.probeheader->nextHop];
				gettimeofday(&stamp, NULL);
				p.probeheader->dates[p.probeheader->nextStamp] = stamp;
				p.probeheader->nextStamp -= 2;
			}
		}

	} else {
		// Si on a rive au dirnier noeud en avancant
		p.probeheader->direction = 1;
		p.probeheader->nextHop--;
		addr1.sin_addr.s_addr = p.probeheader->path[p.probeheader->nextHop];

		gettimeofday(&stamp, NULL);
		p.probeheader->dates[p.probeheader->nextStamp] = stamp;
		p.probeheader->nextStamp--;
	}

	if (!reached) {
		p.to_string();
		//sleep(1);
		if (sendto(sender, (char*) p.msg, p.lenght, 0,
				(struct sockaddr*) &addr1, sizeof(sockaddr_in)) < 0) {
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
