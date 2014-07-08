/*
 * router.cpp
 *
 *  Created on: 6 mai 2014
 *      Author: Anouar
 */

#include "router.h"

namespace std {

router::router() {
	// TODO Auto-generated constructor stub
}

// TODO Remplacer la variable string par une variables path
void router::setPath(uint32_t dest, string spath) {
	d_path p;
	char *pch;
	pch = strtok((char*) (spath.c_str()), "/");
	int i = 0;
	while (pch != NULL) {
		p._path[i] = atoi(pch);
		pch = strtok(NULL, "/");
		i++;
	}
	routingTable.insert(pair<uint32_t, d_path>(dest, p));
}


void router::display() {

	for (map<uint32_t, d_path>::iterator ii = routingTable.begin();
			ii != routingTable.end(); ++ii) {
		cout << (*ii).first << " : " << (*ii).second.tostring() << endl;
	}
}

/*
 * En fonction de la valeur du pxDest contenue dans le paquet, nous cherchons
 * le chemin optimal correspondant. Si la destination ne se trouve pas au
 * niveau de la table de routage nous prenons le chemin direct
 *
 */
void router::lookupforpath(d_packet *p) {

	if (routingTable.find(p->pnchdr->pxDest) == routingTable.end()) {
		p->pnchdr->path[0] = p->pnchdr->pxDest;
		p->pnchdr->pathLen = 1;
		p->pnchdr->nextHop = 1;
	} else {

		d_path path = routingTable.find(p->pnchdr->pxDest)->second;
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
