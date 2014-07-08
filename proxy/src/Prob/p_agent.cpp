/*
 * p_agent.cpp
 *
 *  Created on: 28 mai 2014
 *      Author: Anouar
 *
 */

#include "p_agent.h"
#include <algorithm> 		// Pour utiliser la fonction find pour les maps
<<<<<<< HEAD
=======

>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
namespace std {

/*
 * Variables temporaires pour sauvegarder :
 * le noeud intermédiaire, la destination, les tampons et le 'vector' des
 * chemins déja testés pour chaque destination.
 *
 */

unsigned long hop;
unsigned long dest;
struct timeval stmp, start, finish;
vector<int> already;

p_agent::p_agent(router *r) {

	/*
	 * Récupérer la référence vers l'entité 'Router' pour pouvoir mettre à jour
	 * le chemin selon les résultats obtenues à la fin de chaque opération
	 * de mesure.
	 *
	 */
<<<<<<< HEAD

	myRouter = r;

	/*
	 * Initialiser une structure de donnée de type 'vector' par l'ensemble des
	 * noeuds intermediaires possibles. Tous les proxys SAUF le proxy source
	 * et le proxy destination sont considerés comme des hops valables.
	 * La liste des noeuds est située au niveau du fichier exe/hops.
	 *
	 */

=======

	myRouter = r;

	/*
	 * Initialiser une structure de donnée de type 'vector' par l'ensemble des
	 * noeuds intermediaires possibles. Tous les proxys SAUF le proxy source
	 * et le proxy destination sont considerés comme des hops valables.
	 * La liste des noeuds est située au niveau du fichier exe/hops.
	 *
	 */

>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
	string s;
	ifstream in1("exe/hops");
	if (in1.is_open()) {
		while (!in1.eof()) {
			getline(in1, s);
			index_hops.push_back(inet_addr(s.c_str()));
		}
	}

	/*
	 * Initialiser une structure de donnée de type 'vector' par l'ensemble des
	 * destinations possibles. Les destinations sont inscrites au niveau
	 * du fichier exe/destinations. Les mesures de performance des liens
	 * virtuels se fera donc entre la source exécutant l'agent de mesure et
	 * ces differentes destinations.
	 *
	 */

	ifstream in2("exe/destinations");
	if (in2.is_open()) {
		while (!in2.eof()) {
			getline(in2, s);
			if (s != "")
				index_destinations.push_back(inet_addr(s.c_str()));
		}
	}

	/*
	 * Recuperer l'adresse ip publique du proxy dans la variable myIp
	 * Celle-ci constituera le premier hops des chemins à tester
	 * path[0] = myIp
	 *
	 */

	ifstream in3("exe/myip");
	if (in3.is_open()) {
		getline(in3, myIp);
	}

	/*
	 * Créer l'interface réseau pour l'envoi des paquets de mesures et
<<<<<<< HEAD
	 * initialiser les variables statiques de l'addresse destination
=======
	 * initialiser les variables statiques de la sock addresse
>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
	 * (AF_INET, PROBE_PORT)
	 *
	 */

	probSender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (probSender == -1) {
		cout << "Error creating UDP socket\n";
		exit(1);
	}

	bzero(&add, sizeof(add));
	add.sin_family = AF_INET;
	add.sin_port = htons(PROBE_PORT);
}

<<<<<<< HEAD
=======

>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
int p_agent::execute() {

	/*
	 * Verifier que l'ensemble des destination n'est pas vide
	 *  et initialiser le paquet de mesure.
	 */

	if (index_destinations.size() != 0)
		return 1;
	p.lenght = sizeof(probehdr);
	p.probeheader = p.probe_header();

	/*
	 * Pour chaque destination tester 3 chemins en envoyant 3 paquets
	 * par chemin.
	 *
	 */

	// TODO algo();
	for (unsigned ii = 0; ii < index_destinations.size(); ii++) {

		dest = index_destinations.at(ii);
		already.clear();

		for (int j = 0; j < 3; j++) {

			memset(p.msg, 0, BUFLENGHT);
			p.probeheader->path[0] = inet_addr(myIp.c_str());

			/*
			 * Si j est égale à 0 nous testons le chemin direct de longeur 1
			 * sinon nous testons les autres chemins à un seul saut.
			 *
			 */

			if (j != 0) {

				std::srand(std::time(0));
				int r;
				bool a = true;
				while (a) {
					r = rand() % (index_hops.size());
					if (!(std::find(already.begin(), already.end(), r)
							!= already.end())) {
						a = false;
					}
				}
				hop = index_hops.at(r);
				already.push_back(r);

				p.probeheader->path[1] = hop;
				p.probeheader->path[2] = dest;
				p.probeheader->pathLen = 2;

			} else {
				p.probeheader->path[1] = dest;
				p.probeheader->pathLen = 1;
			}

			for (int j = 0; j < 5; j++) {
				send();
			}
		}
	}
	return 0;
}

<<<<<<< HEAD
=======

>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
void p_agent::send() {

	gettimeofday(&stmp, NULL);
	p.probeheader->direction = 0;
	p.probeheader->nextHop = 1;
	p.probeheader->nextStamp = 2;
	p.probeheader->dates[0] = stmp;

	add.sin_addr.s_addr = p.probeheader->path[p.probeheader->nextHop];
	p.to_string();

	if (sendto(probSender, (char*) p.msg, p.lenght, 0, (struct sockaddr*) &add,
			sizeof(sockaddr_in)) < 0) {
		cerr << "sendto() failed fd here" << endl;
	} else {
		cout << "sent" << endl;
	}
	sleep(2);
}

/*
 * Méthode appellée à la reception d'un paquet de mesure qui arrive
 * à sa destination.
 *
 */

void p_agent::result(p_packet *p) {

	p->to_string();

	// TODO algo();
	// updateMatrix();
	// updateRouter();

	start = p->probeheader->dates[0];
	finish = p->probeheader->dates[1];

	long seconds, useconds, mtime;
	seconds = finish.tv_sec - start.tv_sec;
	useconds = finish.tv_usec - start.tv_usec;
	mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;
	printf("Elapsed time: %ld milliseconds\n", mtime);

	string path;
	string dest;

	for (int i = 1; i < DATA_MAX_PATH_LENGHT; i++) {

		if (p->probeheader->path[i] != 0) {
			std::stringstream ss;
			ss << p->probeheader->path[i];
			string str;
			ss >> str;
			dest = str;
			path.append("/" + str);
		}
	}

	for (map<string, long>::iterator ii = resulTable.begin();
			ii != resulTable.end(); ++ii) {
		if ((*ii).first.compare(path) == 0) {
			(*ii).second = ((*ii).second * 0.3) + (mtime * 0.7);
			break;
		} else {
			resulTable.insert(pair<string, long>(path, mtime));
		}
	}

	if (resulTable.size() == 0) {
		resulTable.insert(pair<string, long>(path, mtime));
	}

	/*
	 * Chercher le meilleur chemin menant vers la destination qu'on a mesurer.
	 * Mettre à jours l'entité 'Router' par le resulatat de la recherche.
	 *
	 */

	long minn = 99999;
	map<string, long>::iterator min;
	std::vector<map<string, long>::iterator> pathToDest;

	for (map<string, long>::iterator ii = resulTable.begin();
			ii != resulTable.end(); ++ii) {

		const char* ptr = strrchr((*ii).first.c_str(), '/');
		if (ptr != NULL)
			ptr++;

		if (dest.compare(ptr) == 0) {
			pathToDest.push_back(ii);
			if ((*ii).second < minn) {
				minn = (*ii).second;
				min = ii;
			}
		}
	}

	myRouter->setPath(atoi(dest.c_str()), (*min).first);
	myRouter->display();

	/*
	 * Nous guarderons que les meilleurs 5 résultats pour chaque destination.
	 *
	 */

	while (pathToDest.size() > 5) {
		unsigned int vectormax;
		long maxx = 0;
		map<string, long>::iterator max;

		for (unsigned int i = 0; i < pathToDest.size(); i++) {
			if ((*pathToDest.at(i)).second > maxx) {
				vectormax = i;
				maxx = (*pathToDest.at(i)).second;
				max = pathToDest.at(i);
			}
		}
		pathToDest.erase(pathToDest.begin() + vectormax);
		resulTable.erase(max);
	}

}

void p_agent::updateRouter() {

}

void p_agent::updateMatrix() {

}

p_agent::~p_agent() {

<<<<<<< HEAD
=======

>>>>>>> c1f14afdf7b575e9f2766ee135d2d9702571aa00
}

} /* namespace std */
