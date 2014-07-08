/*
 * d_path.h
 *
 *  Created on: 6 mai 2014
 *      Author: Anouar
 */

#ifndef D_PATH_H_
#define D_PATH_H_

#include "../panacea.h"

namespace std {

/*
 * Classe qui définie un chemin, et les méthodes getters et setters pour
 * modifier les élément du chemin.
 *
 * TODO peut être améliorer pour servir pour la mise à jours de la table
 * de routage au niveau de p_agnet
 *
 */

class d_path {
public:

	d_path();
	virtual ~d_path();
	void setElement(int i, uint32_t value);
	uint32_t getElement(int i);
	bool equal(d_path *p);
	string tostring();

	uint32_t _path[DATA_MAX_PATH_LENGHT];
};

}
#endif /* D_PATH_H_ */
