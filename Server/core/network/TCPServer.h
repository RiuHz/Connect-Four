#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <sys/types.h> // per ssize_T
#include <sys/socket.h> // per sock_addr_in
#include <netinet/in.h> // per sock_addr_in

int creaSocketServerTCP();
void avviaServer(int socketServer);
void inviaBroadcast(void *datiPacchetto, size_t dimensioneTotale);

#endif