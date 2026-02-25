#include "threads.h"

ThreadData * creaThreadData(Client * client, ServerData * server) {
    ThreadData * thread = malloc(sizeof(ThreadData));
    
    thread -> client = client;
    thread -> server = server;

    return thread;
}

void associaThreadSocket(ServerData * server, int socket) {
    pthread_t tid;
    bool attesaConnessione = true;

    Client * client = creaClient(socket);

    while (attesaConnessione) {
        Messaggio messaggio = attendiMessaggio(client);

        switch (messaggio.tipo) {
            case REQ_CONNECT:
                richiestaConnessione(client, messaggio.payload);
                aggiungiClient(server -> listaClient, client);
                
                attesaConnessione = false;

                eliminaMessaggio(& messaggio);
            break;

            default:
                eliminaMessaggio(& messaggio);
        }
    }

    ThreadData * threadData = creaThreadData(client, server);

    if (pthread_create(&tid, NULL, wrapperAssociaThreadClient, (void *) threadData) != 0) {
        perror("Errore creazione thread");
        exit(1);
    }
}

void * wrapperAssociaThreadClient(void * args) {
    ThreadData * threadData = (ThreadData *) args;

    associaThreadClient(threadData -> server, threadData -> client);

    return NULL;
}

void associaThreadClient(ServerData * server, Client * client) {
    bool richiestaDisconnessione = false;

    while ( !richiestaDisconnessione ) {
        Messaggio messaggio = attendiMessaggio(client);

        switch (messaggio.tipo) {
            case REQ_DISCONNECT:
                richiestaDisconnessione = true;      
            break;

            // Qui vanno aggiunti tutti gli altri casi!

            default:
                eliminaMessaggio(& messaggio);
        }
    }

    close(client -> socket);

    rimuoviClient(server -> listaClient, client);

    pthread_exit(NULL);
}
