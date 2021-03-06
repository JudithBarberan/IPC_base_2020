/*
 * Filename: tcp_client1.c
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 5

void err_sys(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) {
    struct sockaddr_in echoserver;
    char buffer[BUFFSIZE];
    unsigned int echolen;
    int sock, result;
    int received = 0;

    /* Check input arguments */
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip_server> <word> <port>\n", argv[0]);
        exit(1);
    }
    
    /* Try to create TCP socket */
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        err_sys("Error socket");
    }

    /* Set information for sockaddr_in */
    memset(&echoserver, 0, sizeof(echoserver));       /* reset memory */
    echoserver.sin_family = AF_INET;                  /* Internet/IP */
    echoserver.sin_addr.s_addr = inet_addr(argv[1]);  /* IP address */
    echoserver.sin_port = htons(atoi(argv[3]));       /* server port */
    
    /* Try to have a connection with the server */
    result = connect(sock, (struct sockaddr *) &echoserver, sizeof(echoserver));
    if (result < 0) {
        err_sys("Error connect");
    }
    
    /* Just wait */
    while (1);
    
    /* Close socket */
    close(sock);
    
    exit(0);
}
