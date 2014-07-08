/*
 * d_path.cpp
 *
 *  Created on: 6 mai 2014
 *      Author: Anouar
 */

#include "d_path.h"

namespace std {

d_path::d_path() {
	memset(_path, 0, DATA_MAX_PATH_LENGHT * sizeof(uint32_t));
}

void d_path::setElement(int i, uint32_t value) {
	_path[i] = value;
}

bool d_path::equal(d_path *p) {
	bool x = true;
	for (int i = 0; i < DATA_MAX_PATH_LENGHT; i++) {
		if (_path[i] != p->_path[i])
			x = false;
	}
	return x;
}

string d_path::tostring() {
	string ll;

	for (int i = 0; i < DATA_MAX_PATH_LENGHT; i++) {
		std::stringstream ss;
		ss << _path[i];
		string str;
		ss >> str;
		ll.append("/" + str);

	}
	return ll;
}

uint32_t d_path::getElement(int i) {
	return _path[i];
}

d_path::~d_path() {
// TODO Auto-generated destructor stub
}

} /* namespace std */
