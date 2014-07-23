/*
 * router.cpp
 *
 *  Created on: 6 mai 2014
 *      Author: Anouar
 */

#include "router.h"

namespace std {

router::router() {

//	path p;
//	ifstream infile("exe/destinations");
//	if (infile.is_open()) {
//		string line;
//		while (!infile.eof()) {
//			getline(infile, line);
//			routingTable.insert(
//					pair<uint32_t, path>(inet_addr(line.c_str()), p));
//		}
//	}
}

void router::setPath(uint32_t dest, string spath) {
	path p;

	char *pch;
	pch = strtok((char*) (spath.c_str()), "/");
	int i = 0;
	while (pch != NULL) {
		p._path[i] = atoi(pch);
		pch = strtok(NULL, "/");
		i++;
	}
	routingTable.insert(pair<uint32_t, path>(dest, p));
}

void router::display() {

	for (map<uint32_t, path>::iterator ii = routingTable.begin();
			ii != routingTable.end(); ++ii) {
		cout << (*ii).first << " : " << (*ii).second.tostring() << endl;
	}
}

void router::lookupforpath(packet *p) {

	if (routingTable.find(p->pnchdr->pxDdest) == routingTable.end()) {
		p->pnchdr->pathLen = 0;
		p->pnchdr->nextHop = 1;
	} else {

		path path = routingTable.find(p->pnchdr->pxDdest)->second;
		int pathLen = 0;
		// TODO change i = 0
		for (int i = 0; i < DATA_MAX_PATH_LENGHT; i++) {
			p->pnchdr->path[i] = path._path[i];
			if (p->pnchdr->path[i] != 0) {
				pathLen++;
			}
		}
		p->pnchdr->pathLen = pathLen;
		p->pnchdr->nextHop = 1;
	}
}

router::~router() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

