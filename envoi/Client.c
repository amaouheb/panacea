#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv []){
        struct sockaddr_in adrserv;
        char reponse[6];
        int scl = socket(AF_INET, SOCK_STREAM, 0);
	printf("%i\n", scl);
	if (scl != -1){ 
		printf("test1:)\n");
		bzero (&adrserv, sizeof(adrserv));
		adrserv.sin_family = AF_INET;
		inet_aton("140.93.5.118", &adrserv.sin_addr);
		adrserv.sin_port = htons (4522);
		if (connect(scl, (struct sockaddr *)&adrserv, sizeof(adrserv))==0){
			printf("test2:)\n");
			int verif = write(scl, "hello", 6);
			printf("%i\n", verif);
			int lu = read(scl, reponse, 6);
			printf("lu %i\n", lu);
			close(scl);
		}
		else{
			printf("erreur connect\n");
		}
	}
	else{
		printf("erreur création socket\n");
	}


return 0;
}

