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
            case REQ_DISCONNECT: {
                richiestaDisconnessione = true;   
                printf("[Client] [Thread: %lu] Client %s disconnesso su socket %d\n", (unsigned long) pthread_self(), client -> nome, client -> socket);

                eliminaMessaggio(& messaggio);
            }
            break;

            case REQ_CREATE_GAME: {
                printf("[Client] [Thread: %lu] Client %s ha richiesto la creazione di una partita\n", (unsigned long) pthread_self(), client -> nome);
                unsigned int id = creaIDPartita(server -> listaPartite);
                
                Partita * partita = creaPartita(id, client);
                aggiungiPartita(server -> listaPartite, partita);

                Messaggio risposta = rispostaCreaPartita(partita);
                inviaMessaggio(client, risposta);

                Messaggio evento = eventoPartitaCreata(partita);
                accodaMessaggioBroadcast(server -> codaBroadcast, evento);

                eliminaMessaggio(& messaggio);
                eliminaMessaggio(& risposta);
                eliminaMessaggio(& evento);

                gestisciLobby(server, partita);
            }
            break;

            case REQ_JOIN_GAME: {
                unsigned int id = richiestaPartecipaPartita(messaggio.payload);
                printf("[Client] [Thread: %lu] Client %s ha richiesto di entrare nella partita %d\n", (unsigned long) pthread_self(), client -> nome, id);

                Partita * partita = cercaPartita(server -> listaPartite, id);

                if (partita == NULL || avversarioPresente(partita)) {
                    Messaggio risposta = rispostaAccessoPartita(false);

                    inviaMessaggio(client, risposta);

                    eliminaMessaggio(& risposta);
                } else {
                    gestisciRichiestaPartecipazione(server, partita, client);
                }
            }
            break;

            case REQ_GAMES_LIST: {
                printf("[Client] [Thread: %lu] Client %s ha richiesto la lista delle partite...\n", (unsigned long) pthread_self(), client -> nome);
                Messaggio risposta = rispostaListaPartite(server -> listaPartite);

                inviaMessaggio(client, risposta);

                eliminaMessaggio(& messaggio);
                eliminaMessaggio(& risposta);
            }
            break;

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
