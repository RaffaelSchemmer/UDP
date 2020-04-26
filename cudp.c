#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFERSIZE 255
#define PORT 9001

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in sA;
    struct sockaddr_in fA;
    char *servIP = "127.0.0.1";
    char *msg = "Teste de transmissao UDP";
    int fASize, rLen;
    char buffer[BUFFERSIZE];


    /* 1) Cria um socket UDP */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        printf("Erro na criação do socket\n");
        exit(1);
    }

    /* 2) Prepara a estrutura de endereços */
    memset(&sA, 0, sizeof(sA));
    sA.sin_family = AF_INET;
    sA.sin_addr.s_addr = inet_addr(servIP);
    sA.sin_port   = htons(PORT);

    /* 3) Envia uma string para o servidor */
    if (sendto(sock, msg, strlen(msg)+1, 0, (struct sockaddr *)&sA, sizeof(sA)) != (strlen(msg)+1))
    {
        printf("Erro de transmissao\n");
        exit(1);
    }

  
    /* 4) Aguarda resposta: Eco */

    fASize = sizeof(fA);
    if ((rLen = recvfrom(sock, buffer, BUFFERSIZE, 0,(struct sockaddr *) &fA, &fASize)) <= 0)
    {
        printf("Erro de recepcao\n");
        exit(1);
    }

    buffer[rLen] = '\0';
    printf("Recebi o pacote: %s do endereço %s\n", buffer, inet_ntoa(fA.sin_addr));
    
    close(sock);
    exit(0);
}
