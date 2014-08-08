
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv []){

	struct sockaddr_in adrserv;
	struct hostent *sp;
	struct in_addr ipv4addr;
	char *requete = "hello";
	char reponse[10];
	int scli =socket(AF_INET, SOCK_DGRAM, 0);
	bzero (&adrserv, sizeof(adrserv));
	adrserv.sin_family = AF_INET;
	inet_pton(AF_INET, "140.93.5.118", &ipv4addr);
	sp = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
	//sp =gethostbyadr("140.93.5.118",4,AF_INET); //assume OK
	memcpy (&adrserv.sin_addr, sp->h_addr_list[0], sp->h_length);
	adrserv.sin_port = htons (4522);
	sendto(scli, requete, strlen(requete), 0,(struct sockaddr *)&adrserv, sizeof(adrserv));
	recvfrom(scli, reponse, sizeof (reponse), 0, NULL, NULL);
	close (scli);
}
