/*
 * ProbeRTT.cpp
 *
 *  Created on: 28 mai 2014
 *      Author: Anouar
 */

#include "p_agent.h"
#include <algorithm>

namespace std {

struct timeval stmp, start, finish;
vector<int> already; /* Need this vector a unique path */
unsigned long hop;
unsigned long dest;
router *rr;

p_agent::p_agent(router *r) {

	rr = r;
	string s; /* Line */

	ifstream in1("exe/hops");
	if (in1.is_open()) {
		while (!in1.eof()) {
			getline(in1, s);
			index_hops.push_back(inet_addr(s.c_str()));
		}
	}

	ifstream in2("exe/destinations");
	if (in2.is_open()) {
		while (!in2.eof()) {
			getline(in2, s);
			if (s != "")
				index_destinations.push_back(inet_addr(s.c_str()));
		}
	}

	ifstream in4("exe/myip");
	if (in4.is_open()) {
		getline(in4, myIp);
	}

	// sender
	probSender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (probSender == -1) {
		cout << "Error creating UDP socket\n";
		exit(1);
	}
}

int random_in_range(unsigned int max) {
	return (rand() % max); /* in [0, RAND_MAX[ */
}

void p_agent::execute() {

	if (index_destinations.size() != 0) {

		p.lenght = sizeof(probehdr);
		p.probeheader = p.probe_header();

		bzero(&add, sizeof(add));
		add.sin_family = AF_INET;
		add.sin_port = htons(PROBE_PORT);

		// LOOP 1: Send to all destination
		for (unsigned ii = 0; ii < index_destinations.size(); ii++) {

			dest = index_destinations.at(ii);
			already.clear();

			// LOOP 2: For each path
			for (int j = 0; j < 3; j++) {

				memset(p.msg, 0, BUFLENGHT);
				p.probeheader->direction = 0;
				p.probeheader->nextHop = 1;
				p.probeheader->path[0] = inet_addr(myIp.c_str());
				hop = 0;

				/*
				 * At iteration 0
				 * direct path will be examined
				 */

				//for(unsigned int i=0; i< index_hops.size(); i++){
				//	cout <<" " << index_hops.at(i);
				//	}
				//exit(0);

				if (j != 0 ){ //&& 1 == 0) { // TODO remove && 1 == 0

					std::srand(std::time(0));
					int r;
					bool a = true;
					while (a) {
						r = random_in_range(index_hops.size());
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

				p.probeheader->nextStamp += 2;

				for (int j = 0; j < 3; j++) {

					gettimeofday(&stmp, NULL);
					p.probeheader->dates[0] = stmp;

					/* Now that our packet is ready for this destination
					 * send it NUMBER_OF_PACKET time
					 */

					add.sin_addr.s_addr =
							p.probeheader->path[p.probeheader->nextHop];
					p.to_string();
					if (sendto(probSender, (char*) p.msg, p.lenght, 0,
							(struct sockaddr*) &add, sizeof(sockaddr_in)) < 0) {
						cerr << "sendto() failed fd here" << endl;
					} else {
						cout << "sent" << endl;
					}
					sleep(2);
				}
			}
		}
	}
}

/*
 * Called by the forwarder when recieving a packet that contains resulats
 */
void p_agent::result(p_packet *p) {
	cout << "result" << endl;
	p->to_string();

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
			//cout << p->probeheader->path[i] << endl;
		}
	}
	//cout << "path: " << path << endl;
	//exit(0);
	//cout << path << endl;

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
	 * Find the best path and Keep only 5 path to the given destionation
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

	rr->setPath(atoi(dest.c_str()), (*min).first);
	rr->display();
	//exit(0);
}

p_agent::~p_agent() {
// TODO Auto-generated destructor stub
}

} /* namespace std */
