/*
 * packet.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef PACKET_H_
#define PACKET_H_


#include "../panacea.h"

namespace std {

class packet {
public:
	packet();
	virtual ~packet();
	struct panaceahdr * panacea_header();
	struct iphdr * original_ip_header();
	void to_string();

	unsigned char msg[BUFLENGHT];
	unsigned lenght;

	struct iphdr *originaliphdr;
	struct panaceahdr *pnchdr;
};

} /* namespace std */
#endif /* PACKET_H_ */


