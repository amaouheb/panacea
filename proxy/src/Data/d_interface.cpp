/*
 * d_interface.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#include "d_interface.h"

namespace std {

d_interface::d_interface(router *r) {

	/*
	 * Pour pouvoir consulter la table de routage nous devons faire passer
	 * sa référence 'myRouter' au forwarder des paquets datas.
	 *
	 */
	myRouter = r;

	/*
	 * Créer une socket et l'associer avec le port 'DATA_PORT'
	 */
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

void d_interface::process() {
	p.lenght = recvfrom(sd, p.msg, sizeof(d_packet) - 1, 0,
			(struct sockaddr *) &vm, &slen);
	p.to_string();
	f.dispatch(&p, myRouter);
}

d_interface::~d_interface() {

}

} /* namespace std */
