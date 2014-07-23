/*
 * path.h
 *
 *  Created on: 6 mai 2014
 *      Author: Anouar
 */

#ifndef PATH_H_
#define PATH_H_

#include "../panacea.h"

namespace std {

class path {
public:

	path();
	virtual ~path();
	void setElement(int i, uint32_t value);
	uint32_t getElement(int i);
	bool equal(path *p);
	string tostring();

	uint32_t _path[DATA_MAX_PATH_LENGHT];
};

} /* namespace std */
#endif /* PATH_H_ */

