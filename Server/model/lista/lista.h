#ifndef LISTA_H
#define LISTA_H

#include <pthread.h>

#include "../client/client.h"
#include "../partita/partita.h"

typedef struct ListaClient {
    pthread_mutex_t mutex;
    Client * head;
    unsigned int contatore;
} ListaClient;

typedef struct ListaPartite {
    pthread_mutex_t mutex;
    Partita * head;
    unsigned int contatore;
} ListaPartite;

void aggiungiClient(ListaClient * lista, Client * client);
void stampaListaClient(ListaClient * lista);
void rimuoviClient(ListaClient * lista, Client * client);

void aggiungiPartita(ListaPartite * lista, Partita * partita);
void stampaListaPartite(ListaPartite * lista);
void rimuoviPartita(ListaPartite * lista, Partita * partita);

#endif
