/*
 * router.h
 *
 *  Created on: 6 mai 2014
 *      Author: root
 */

#ifndef ROUTER_H_
#define ROUTER_H_

#include "packet.h"
#include "path.h"

namespace std {

class router {
public:

	router();
	virtual ~router();
	void lookupforpath(packet *p);
	void setPath(uint32_t dest,string path);
	void display();

	std::map<uint32_t, path> routingTable;
};

} /* namespace std */
#endif /* ROUTER_H_ */

