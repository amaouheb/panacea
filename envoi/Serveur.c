#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv []){

        struct sockaddr_in adrserv;
        int sserv =socket(AF_INET, SOCK_STREAM, 0);
	printf("debut %i\n", sserv);
	if (sserv != -1){
        	bzero (&adrserv, sizeof(adrserv));
        	adrserv.sin_family = AF_INET;
        	adrserv.sin_addr.s_addr = htonl (INADDR_ANY);
        	adrserv.sin_port = htons (4522);
		printf("avant\n");
        	if(bind(sserv, (struct sockaddr *)&adrserv, sizeof(adrserv))==0){
			printf("test2:)\n");
			if (listen(sserv,5)==0){
				printf("test3:)\n");
        			while (1) {
                			char requete[6];
                			int scl =accept(sserv, NULL, NULL);
					printf("accept %i\n", scl);
                			int lu = read(scl, requete, 6);
					printf("lu %i\n", lu);
                			if (strcmp(requete, "hello") == 0){
						printf("test4:)\n");
						int verif = write (scl, "world", 6);
						
					}	
                			else {
						write (scl, "bouh", 5);
					}
                			close (scl);
        			}
			}
			else {
				printf("erreur listen\n");
			}	
		}
		else {
			printf("erreur bind\n");
		}
	}
	else{ 
	printf("erreur création socket\n");
	}

return 0;
}

