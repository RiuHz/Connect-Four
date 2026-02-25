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

#include "../../core/threading/threads.h"

#include "../../data/list/list.h"

#include "../messaggio/messaggio.h"
#include "../shared/protocol.h"

typedef struct ServerData {
    int socket;
    struct sockaddr_in address;
    ListaClient * listaClient;
    ListaPartite * listaPartite;
} ServerData;

ServerData * creaSocketServerTCP(void);

void impostaParametriServer(ServerData * server);
void inizializzaListeServer(ServerData * server);

void avviaServer(ServerData * server);

void inviaBroadcast(ServerData * server, Messaggio messaggio);

Messaggio attendiMessaggio(Client * client);
void leggiFlussoDati(Client * client, void * buffer, size_t lunghezza);

void inviaMessaggio(Client * client, Messaggio messaggio);
void inviaFlussoDati(Client * client, uint32_t * buffer, size_t dimensione);

#endif
