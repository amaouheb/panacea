/*
 * agent.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#include "p_interface.h"

namespace std {

p_interface::p_interface(p_agent *a) {

	/*
	 * Pour pouvoir faire passer à l'agent de mesure les paquets qui ont
	 * fait le tour pour les analyser, nous aurons besoin de faire passer
	 * ce pointeur au forwarder.
	 *
	 */
	myAgent = a;

	/*
	 * Créer une socket et l'associer avec le port 'PROBE_PORT'
	 */
	socketDescription = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socketDescription == -1) {
		cout << "Error creating DGRAM socket\n";
		exit(1);
	}

	bzero(&proxyAddr, sizeof(sockaddr));
	proxyAddr.sin_family = AF_INET;
	proxyAddr.sin_port = htons(PROBE_PORT);
	proxyAddr.sin_addr.s_addr = htonl(INADDR_ANY );

	int err = bind(socketDescription, (struct sockaddr *) &proxyAddr,
			sizeof(sockaddr));
	if (err < 0) {
		cout << "Error binding socket" << err << endl;
		exit(1);
	}
	socketLen = sizeof(proxyAddr);
}

void p_interface::process() {
	p.lenght = recvfrom(socketDescription, p.msg, sizeof(p_packet) - 1, 0,
			(struct sockaddr *) &proxyAddr, &socketLen);
	p.to_string();
	f.process(&p, myAgent);
}

p_interface::~p_interface() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
