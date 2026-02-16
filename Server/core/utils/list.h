#ifndef LIST_H
#define LIST_H

// Strutture dati necessarie
typedef struct ListaClient {
        int socketClient;
        struct ListaClient *next;
} ListaClient;


void aggiungiClient(int nuovoClientConnesso);
void stampaLista();
void rimuoviClient(int clientDisconnesso);

#endif