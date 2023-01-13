#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#define MAXSIZE 516

int main(int argc, char ** argv) {
    if(argc!=4){
        printf("Wrong usage.\nPlease use %s hostname port file", argv[0]);
        exit (EXIT_FAILURE);
    }
    printf("Welcome to 2g1tp1's implementation of a tftp client\n");
    printf("sending %s to the host :%s@%s\n",argv[3],argv[1],argv[2]);
    struct addrinfo *result;
    struct addrinfo hints;
    memset(&hints,0, sizeof (struct addrinfo));
    hints.ai_family= AF_INET;
    hints.ai_protocol=IPPROTO_UDP;

    int status;
    status=getaddrinfo(argv[1],argv[2],&hints,&result);
    if(status==-1){
        printf("it seems like I cant't find the hist %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    char fileName;
    fileName=malloc(strlen(argv[2]));
    strcpy(fileName,argv[2]);
    char buffer[MAXSIZE]={0};
    buffer[1]=2;
    sprintf(buffer+2,"%s",fileName);
    sprintf(buffer+3+strlen(fileName),"NESTASCII");

    int sock =socket(hints.ai_family,hints.ai_socktype,hints.ai_family);

    if(sock == -1){
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    sendto(sock, buffer,12+ strlen(argv[3]),0,result->ai_addr,result->ai_addrlen);

    return EXIT_SUCCESS;

    printf("ending %s to the host :%s@%s\n",argv[3],argv[1],argv[2]);
    return 0;
}
