#ifndef SERVER_HPP
#define SERVER_HPP

#include "../coda/coda.h"
#include "../lista/lista.h"

typedef struct Server {
    int socket;
    struct sockaddr_in address;
    ListaClient * listaClient;
    ListaPartite * listaPartite;
    CodaBroadcast * codaBroadcast;
} Server;

void impostaParametriServer(Server * server);
void inizializzaListeServer(Server * server);

#endif
