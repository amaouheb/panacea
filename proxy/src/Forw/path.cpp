/*
 * Path.cpp
 *
 *  Created on: 6 mai 2014
 *      Author: Anouar
 */

#include "path.h"

namespace std {

path::path() {
	memset(_path, 0, DATA_MAX_PATH_LENGHT * sizeof(uint32_t));
	//_path[0] = inet_addr("172.16.128.103"); //172.16.128.103
	//_path[1] = inet_addr("172.16.128.104");
}

void path::setElement(int i, uint32_t value) {
	_path[i] = value;
}

bool path::equal(path *p) {
	bool x = true;
	for (int i = 0; i < DATA_MAX_PATH_LENGHT; i++) {
		if (_path[i] != p->_path[i])
			x = false;
	}
	return x;
}

string path::tostring() {
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

uint32_t path::getElement(int i) {
	return _path[i];
}

path::~path() {
// TODO Auto-generated destructor stub
}

} /* namespace std */

