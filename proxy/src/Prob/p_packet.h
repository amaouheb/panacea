/*
 * p_packet.h
 *
 *  Created on: May 2, 2014
 *      Author: Anouar
 */

#ifndef P_PACKET_H_
#define P_PACKET_H_

#include "../panacea.h"

namespace std {

class p_packet {

public:
	p_packet();
	virtual ~p_packet();
	struct probehdr * probe_header();
	void to_string();

	unsigned char msg[BUFLENGHT];
	unsigned lenght;
	struct probehdr *probeheader;
};

} /* namespace std */
#endif /* P_PACKET_H_ */

