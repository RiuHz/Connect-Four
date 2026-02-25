#include "threads.h"

ThreadData * creaThreadData(ServerData * server, int socket) {
    ThreadData * thread = malloc(sizeof(ThreadData));
    
    thread -> server = server;
    thread -> socket = socket;

    return thread;
}

void associaThreadSocket(ServerData * server, int socket) {
    pthread_t thread;

    ThreadData * threadData = creaThreadData(server, socket);

    if (pthread_create(& thread, NULL, wrapperThread, (void *) threadData) != 0) {
        perror("Errore creazione thread");
        exit(1);
    }
}

void * wrapperThread(void * arg) {
    ThreadData * thread = (ThreadData *) arg;

    Client * client = attendiConnessioneClient(thread -> server, thread -> socket);

    gestisciRichiesteClient(thread -> server, client);

    return NULL;
}

Client * attendiConnessioneClient(ServerData * server, int socket) {
    bool attesaConnessione = true;
 
    Client * client = creaClient(socket);

    while (attesaConnessione) {
        Messaggio messaggio = attendiMessaggio(client);

        switch (messaggio.tipo) {
            case REQ_CONNECT:
                richiestaConnessione(client, messaggio.payload);
                aggiungiClient(server -> listaClient, client);
                
                attesaConnessione = false;
                printf("[Thread: %lu] Client %s connesso su socket %d\n", (unsigned long) pthread_self(), client -> nome, client -> socket);

                eliminaMessaggio(& messaggio);
            break;

            default:
                eliminaMessaggio(& messaggio);
        }
    }

    return client;
}

void gestisciRichiesteClient(ServerData * server, Client * client) {
    bool richiestaDisconnessione = false;

    while ( !richiestaDisconnessione ) {
        Messaggio messaggio = attendiMessaggio(client);

        switch (messaggio.tipo) {
            case REQ_DISCONNECT:
                richiestaDisconnessione = true;   
                printf("[Thread: %lu] Client %s disconnesso su socket %d\n", (unsigned long) pthread_self(), client -> nome, client -> socket);
            break;

            // Qui vanno aggiunti tutti gli altri casi!

            default:
                eliminaMessaggio(& messaggio);
        }
    }

    close(client -> socket);
    printf("[Thread: %lu] Chiusa la socket %d\n", (unsigned long) pthread_self(), client -> socket);

    rimuoviClient(server -> listaClient, client);
    printf("[Thread: %lu] Rimosso il Client, chiusura del thread...\n", (unsigned long) pthread_self());

    pthread_exit(NULL);
}
