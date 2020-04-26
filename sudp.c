#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 255
#define PORTA 9001


int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in sA; // endere�o do cliente
    struct sockaddr_in cA; // endere�o do servidor
    unsigned int cALen;     // tamanho da estrutura de endere�o do cliente
    char Buffer[BUFSIZE];  // buffer de recep��o
    int rMSize;                  // quantidade de dados recebidos

    
	printf("Servidor UDP\n");

    /* Cria um socket UDP */

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
        	printf("erro na criacao do socket\n");
		exit(1);
	}

    /* Define o endere�o do servidor */

 	memset(&sA, 0, sizeof(sA));
    	sA.sin_family = AF_INET;
    	sA.sin_addr.s_addr = htonl(INADDR_ANY);
    	sA.sin_port = htons(PORTA);

 	/* Associa o socket ao endere�o do servidor */
 	if (bind(sock, (struct sockaddr *) &sA, sizeof(sA)) < 0)
   	{
        	printf("erro no bind\n");
		exit(1);
	}

	/* Aguarda pacotes dos clientes */

	for (;;)
	{

	        cALen = sizeof(cA);
        	if ((rMSize = recvfrom(sock, Buffer, BUFSIZE, 0,(struct sockaddr *) &cA, &cALen)) < 0)
 	 	{
        		printf("erro na recepcao\n");
			exit(1);
		}

        	printf("Recebi um pacote do cliente %s\n", inet_ntoa(cA.sin_addr));


		 if (sendto(sock, Buffer, rMSize, 0,(struct sockaddr *) &cA, sizeof(cA)) != rMSize)
 	 	{
        		printf("Erro na transmiss�o\n");
			exit(1);
		}
	}

}
