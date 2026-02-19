#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <pthread.h>

#include "../../data/list/list.h"
#include "../../threading/threads.h"

#include "../shared/protocol.h"

typedef struct ServerData {
    int socket;
    struct sockaddr_in address;
    ListaClient listaClient;
    ListaPartite listaPartite;
} ServerData;

ServerData * creaSocketServerTCP();

void impostaParametriServer(ServerData * server);
void inizializzaListeServer(ServerData * server);

void avviaServer(ServerData * server);

void inviaBroadcast(ServerData * server, void *datiPacchetto, size_t dimensioneTotale);

#endif
