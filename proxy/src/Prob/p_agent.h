/*
 * p_agent.h
 *
 *  Created on: 28 mai 2014
 *      Author: Anouar
 */

#ifndef P_AGENT_H_
#define P_AGENT_H_

#include "p_packet.h"
#include "../Data/d_path.h"
#include "../router.h"

namespace std {

class p_agent {
public:
	p_agent(router *r);
	virtual ~p_agent();
<<<<<<< HEAD
	// Créer les paquets de mesure selon un algorithme à preciser/
	int execute();
	// Appellée à la fin de la methode execute pour l'envoi des paquets
	void send();
=======


	// Créer les paquets de mesure selon un algorithme à preciser/
	int execute();

	// Appellée à la fin de la methode execute pour l'envoi des paquets
	void send();

>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
	// Appellée automatiquement à la reception d'un paquet qui a fait le tour
	void result(p_packet *p);
	void updateMatrix();
	void updateRouter();

<<<<<<< HEAD
=======

	void updateMatrix();
	void updateRouter();

>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
	/*
	 * Création de l'interface d'envoi et instanciation d'un objet p_paquet
	 */
	int probSender;
	struct sockaddr_in add;
	p_packet p;

	// Structure pour contenir les hops
	std::vector<unsigned long> index_hops;
	// Structure pour contenir les destinations
	std::vector<unsigned long> index_destinations;
	// SMon adresse IP
	string myIp;
	// Structure pour guarder les resultats de mesure
	std::map<string, long> resulTable;
	// Référence à la table de routage
	router *myRouter;
};

} /* namespace std */
#endif /* P_AGENT_H_ */
