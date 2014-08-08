
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv []){

	struct sockaddr_in adrserv, adrcli; 
	char requete[10];
	int sserv = socket(AF_INET, SOCK_DGRAM, 0);
	bzero (&adrserv, sizeof(adrserv));
	adrserv.sin_family = AF_INET;
	adrserv.sin_addr.s_addr = htonl (INADDR_ANY);
	adrserv.sin_port = htons (4522);
	bind(sserv, (struct sockaddr*)&adrserv, sizeof(adrserv));
	while (1) {
		bzero (&adrcli, sizeof (adrcli));
		int adrclilen = sizeof (adrcli);
		recvfrom(sserv, requete, sizeof(requete), 0,(struct sockaddr *)&adrcli, &adrclilen);
		sendto(sserv, "world", 6, 0,(struct sockaddr *)&adrcli, adrclilen);
	}
}
