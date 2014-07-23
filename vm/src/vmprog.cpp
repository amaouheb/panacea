/*
 * vmprog.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: Anouar
 */

#include "panacea.h"

using namespace std;

/* NFQUEUE */

struct nfq_handle *nfqHandle;
struct nfq_q_handle *myQueue;
struct nfnl_handle *netlinkHandle;
int fd, res;
char buf[BUFLENGHT];

/* SOCKET */
struct sockaddr_in proxyAddr;
int sockfd, socklen;

/* LOCAL VAR */

string proxyIp;
std::map<unsigned long, unsigned long> vmPx;

void Xprintf(char *packet, unsigned int len) {
	int j = 1;
	for (unsigned int i = 0; i < len; i++) {
		if ((j % 17) == 0) {
			j = 1;
			printf("\n");
		}
		if ((unsigned char) packet[i] <= 15)
			printf(" 0%1X ", (unsigned char) packet[i]);
		else
			printf(" %1X ", (unsigned char) packet[i]);
		j++;
	}
	cout << endl << endl;
}

static int Callback(nfq_q_handle *myQueue, struct nfgenmsg *msg, nfq_data *pkt,
		void *cbData) {

	uint32_t id = 0;
	nfqnl_msg_packet_hdr *header;
	if ((header = nfq_get_msg_packet_hdr(pkt))) {
		id = ntohl(header->packet_id);
	}

	unsigned char *load;
	unsigned int loadLenght;
	loadLenght = nfq_get_payload(pkt, (char**) &load);
	//loadLenght = nfq_get_payload(pkt, &load);
	Xprintf((char*) load, loadLenght);

	char message[BUFLENGHT];
	unsigned int msgLenght;

	struct panaceahdr *pnchdr;
	struct iphdr *originaliphdr;

	pnchdr = (panaceahdr*) message;
	originaliphdr = (iphdr *) (message + sizeof(panaceahdr));
	memcpy(message + sizeof(panaceahdr), load, loadLenght);
	msgLenght = loadLenght + sizeof(panaceahdr);

	pnchdr->pxDest = vmPx[originaliphdr->daddr];
	pnchdr->nbrHops = 0; //nombre de hops utilisés sur ces quatres
	pnchdr->nextHop = 0;

	/*
	 * Reinjection du paquet
	 */
	Xprintf((char*) message, msgLenght);

	if (sendto(sockfd, message, msgLenght, 0, (struct sockaddr*) &proxyAddr,
			socklen) == -1)
		printf("sendto()");

	return nfq_set_verdict(myQueue, id, NF_DROP, msgLenght,
			(unsigned char*) message);
}
int main(int argc, char **argv) {

	/*
	 * VAR INITIALISATION
	 */

	ifstream in2("exe/proxy");
	if (in2.is_open()) {
		getline(in2, proxyIp);
		in2.close();

	}

	ifstream infile("exe/resolution");
	if (infile.is_open()) {
		string line;
		while (!infile.eof()) {

			getline(infile, line);
			char *l = const_cast<char*>(line.c_str());

			char *px, *vm;
			px = strtok(l, ",");
			vm = strtok(NULL, ",");

			while (vm != NULL) {
				vmPx.insert(
						pair<unsigned long, unsigned long>(inet_addr(vm),
								inet_addr(px)));
				vm = strtok(NULL, ",");
			}
		}
		infile.close();
	}

	/*
	 * SOCKET INITIALISATION
	 */

	socklen = sizeof(proxyAddr);
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		printf("csocket");
	bzero(&proxyAddr, sizeof(proxyAddr));

	proxyAddr.sin_family = AF_INET;
	proxyAddr.sin_port = htons(DATA_PORT);

	if (inet_aton(proxyIp.c_str(), &proxyAddr.sin_addr) == 0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	/*
	 * NFQUEUE INITIALISATION
	 */

	if (!(nfqHandle = nfq_open())) {
		cerr << "Error in nfq_open()" << endl;
		exit(-1);
	}
	if (nfq_unbind_pf(nfqHandle, AF_INET) < 0) {
		cerr << "Error in nfq_unbind_pf()" << endl;
		exit(1);
	}
	if (nfq_bind_pf(nfqHandle, AF_INET) < 0) {
		cerr << "Error in nfq_bind_pf()" << endl;
		exit(1);
	}

	if (!(myQueue = nfq_create_queue(nfqHandle, 0, &Callback, NULL))) {
		cerr << "Error in nfq_create_queue()" << endl;
		exit(1);
	}
	if (nfq_set_mode(myQueue, NFQNL_COPY_PACKET, 0xffff) < 0) {
		cerr << "Could not set packet copy mode" << endl;
		exit(1);
	}

	netlinkHandle = nfq_nfnlh(nfqHandle);
	fd = nfnl_fd(netlinkHandle);

	cout << "Waiting.." << endl;
	while ((res = recv(fd, buf, sizeof(buf), 0)) && res >= 0) {
		nfq_handle_packet(nfqHandle, buf, res);
	}

	nfq_destroy_queue(myQueue);
	nfq_close(nfqHandle);

	return 0;
}
