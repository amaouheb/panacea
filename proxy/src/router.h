/*
 * router.h
 *
 *  Created on: 6 mai 2014
 *      Author: root
 */

#ifndef ROUTER_H_
#define ROUTER_H_

#include "Data/d_packet.h"
#include "Data/d_path.h"

namespace std {

class router {
public:

	router();
	virtual ~router();
	/*
	 * Methode utiliser par l'agent de routage des paquets data pour récuperer
	 * un chemin menant vers une destination donnée
	 *
	 */
	void lookupforpath(d_packet *p);

	/* Methode utiliser par l'agent de mesure pour mettre à jour une entrée
	 * Il est important de noter que la structure map n'autorise pas
	 * de redondance de clé.
	 *
	 */
	void setPath(uint32_t dest, string path);
	void display();

	/*
	 * TABLE DE ROUTAGE :
	 * Pour chaque destination 'dest' on associe un chemin 'path'
	 * Une destination est un entier sur 32 bits 54.92.22.35 = 5888667958
	 * Un chemin est un tableau d'adresse path[0] = 5888667958 ...
	 *
	 */
	std::map<uint32_t, d_path> routingTable;
};

}
#endif /* ROUTER_H_ */
