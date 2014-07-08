#include "packet.h"

using namespace std;

ushort checksum(unsigned short *buffer, int size) {
	unsigned long cksum = 0;
	while (size > 1) {
		cksum += *buffer++;
		size -= sizeof(ushort);
	}
	if (size) {
		cksum += *(unsigned char*) buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (unsigned short) (~cksum);
}


int main(int argc, char **argv) {

	packet p;

	// reciever socket
	int sd;
	struct sockaddr_in add, vm;
	socklen_t slen;

	sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd == -1) {
		cout << "Error creating raw socket\n";
		exit(1);
	}

	bzero(&add, sizeof(add));
	add.sin_family = AF_INET;
	add.sin_port = htons(DATA_PORT);
	add.sin_addr.s_addr = htonl(INADDR_ANY );

	int err = bind(sd, (struct sockaddr *) &add, sizeof(sockaddr));
	if (err < 0) {
		cout << "Error binding socket" << err << endl;
		exit(1);
	}
	slen = sizeof(vm);


	struct sockaddr_in rawaddr;
	
	int raw = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (raw == -1) {
		cout << "Error creating RAW socket\n";
		exit(1);
	}

	const int on = 1;
	if (setsockopt(raw, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
		cerr << "setsockopt() failed to set IP_HDRINCL fd" << endl;
	}
	
	bzero(&rawaddr, sizeof(rawaddr));
	rawaddr.sin_family = AF_INET;


	while (1) {
		cout << "Waiting..." << endl;
		p.lenght = recvfrom(sd, p.msg, sizeof(packet) - 1, 0,
				(struct sockaddr *) &vm, &slen);

		int j = 1;
        	for (unsigned int i = 0; i < p.lenght; i++) {
                	if ((j % 17) == 0) {
                        	j = 1;
                        	printf("\n");
                	}
                	if (p.msg[i] <= 15)
                        	printf(" 0%1X ", p.msg[i]);
                	else
                        	printf(" %1X ", p.msg[i]);
                	j++;
        	}
        	cout << endl << endl;
	
		
		cout << "desencapsulate" << endl;
		p.pnchdr = p.panacea_header();
		p.originaliphdr = p.original_ip_header();
		
		p.originaliphdr->saddr = p.pnchdr->vmSrc;
		p.originaliphdr->check = checksum((unsigned short*) p.originaliphdr, sizeof(iphdr));
		int res = htons (p.originaliphdr->tot_len);
		rawaddr.sin_addr.s_addr = p.originaliphdr->daddr;
	
		packet pp;
		memcpy(pp.msg, p.msg + sizeof(panaceahdr), res);
		pp.lenght = res;
		
		j = 1;
		for (unsigned int i = 0; i < pp.lenght; i++) {
        		if ((j % 17) == 0) {
        	              	j = 1;
        	             	printf("\n");
        	       	}
        	  	if (pp.msg[i] <= 15)
        	         	printf(" 0%1X ", pp.msg[i]);
               		else
                       		printf(" %1X ", pp.msg[i]);
               		j++;
        	}
        	cout << endl << endl;
        	
        	if (sendto(raw, (char*) pp.msg, pp.lenght, 0,(struct sockaddr*) &rawaddr, sizeof(sockaddr_in)) < 0) {
			cerr << "sendto() failed fd" << endl;
		} else {
		cout << "sent" << endl;
		}
	
	}
	return 0;
}
