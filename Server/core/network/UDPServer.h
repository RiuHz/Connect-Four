#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <sys/types.h> // per ssize_T
#include <sys/socket.h> // per sock_addr_in
#include <netinet/in.h> // per sock_addr_in

int creaSocketServerUDP();
void avviaServer(int socketServer);
void associaThreadClient(int socket, struct sockaddr_in addr, char *buffer, ssize_t len);
void *inviaMessaggio(void *arg);

#endif