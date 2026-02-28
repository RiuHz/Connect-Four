#include "client.h"

Client * attendiConnessioneClient(Server * server, int socket) {
    bool attesaConnessione = true;
    
    Client * client = creaClient(socket);
    
    printf("[Client] [Thread: %lu] In attesa della richiesta di connessione sul socket %d\n", (unsigned long) pthread_self(), client -> socket);

    while (attesaConnessione) {
        Messaggio messaggio = attendiMessaggio(client);

        switch (messaggio.header.type) {
            case REQ_CONNECT:
                richiestaConnessione(client, messaggio.payload);
                aggiungiClient(server -> listaClient, client);
                
                attesaConnessione = false;
                printf("[Client] [Thread: %lu] Client %s connesso su socket %d\n", (unsigned long) pthread_self(), client -> nome, client -> socket);

                eliminaMessaggio(& messaggio);
            break;

            default:
                eliminaMessaggio(& messaggio);
        }
    }

    return client;
}

void gestisciRichiesteClient(Server * server, Client * client) {
    bool richiestaDisconnessione = false;

    while ( !richiestaDisconnessione ) {
        Messaggio messaggio = attendiMessaggio(client);

        switch (messaggio.header.type) {
            case REQ_DISCONNECT:
                richiestaDisconnessione = true;   
                printf("[Client] [Thread: %lu] Client %s disconnesso su socket %d\n", (unsigned long) pthread_self(), client -> nome, client -> socket);
            break;

            // Qui vanno aggiunti tutti gli altri casi!

            default:
                eliminaMessaggio(& messaggio);
        }
    }

    close(client -> socket);
    printf("[Client] [Thread: %lu] Chiusa la socket %d\n", (unsigned long) pthread_self(), client -> socket);

    rimuoviClient(server -> listaClient, client);
    printf("[Client] [Thread: %lu] Rimosso il Client, chiusura del thread...\n", (unsigned long) pthread_self());

    pthread_exit(NULL);
}
