#include "server.h"

void impostaParametriServer(Server * server) {
    memset(& server -> address, 0, sizeof(server -> address));
    server -> address.sin_family = AF_INET;
    server -> address.sin_addr.s_addr = htonl(INADDR_ANY);
    server -> address.sin_port = htons(SERVER_PORT);
}

void inizializzaListeServer(Server * server) {
    server -> listaClient = malloc(sizeof(ListaClient));
    pthread_mutex_init(& server -> listaClient -> mutex, NULL);
    server -> listaClient -> head = NULL;

    server -> listaPartite = malloc(sizeof(ListaPartite));
    pthread_mutex_init(& server -> listaPartite -> mutex, NULL);
    server -> listaPartite -> head = NULL;

    server -> codaBroadcast = malloc(sizeof(CodaBroadcast));
    pthread_mutex_init(& server -> codaBroadcast -> mutex, NULL);
    sem_init(& server -> codaBroadcast -> semaforo, 0, 1);
    server -> codaBroadcast -> head = NULL;
    server -> codaBroadcast -> tail = NULL;
}
