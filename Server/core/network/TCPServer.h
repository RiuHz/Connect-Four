#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <sys/types.h> // per ssize_T
#include <sys/socket.h> // per sock_addr_in
#include <netinet/in.h> // per sock_addr_in

int creaSocketServerTCP();
void avviaServer(int socketServer);


#endif