#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void aggiungiClient(ListaClient * lista, Client * client) {
    pthread_mutex_lock(& lista -> mutex);

    client -> next = lista -> head;
    lista -> head = client;
    lista -> contatore += 1;

    pthread_mutex_unlock(& lista -> mutex);
}

void stampaListaClient(ListaClient * lista) {
    Client * corrente = lista -> head;

    pthread_mutex_lock(& lista -> mutex);

    if (corrente == NULL) {
        printf("La lista dei Client e' vuota\n");  
    } else {
        printf("Lista client: ");

        while(corrente != NULL) {
            printf("%d - %s\n", corrente -> socket, corrente -> nome);
            corrente = corrente -> next;
        }  
    }

    pthread_mutex_unlock(& lista -> mutex);
}

void rimuoviClient(ListaClient * lista, Client * client) {

    pthread_mutex_lock(& lista -> mutex);

    Client * corrente = lista -> head;
    Client * precedente = NULL;

    while (corrente != NULL && corrente -> socket != client -> socket) {
        precedente = corrente;
        corrente = corrente -> next;
    }

    if (corrente != NULL) {

        if (precedente == NULL) {
            lista -> head = corrente -> next;
        } else {
            precedente -> next = corrente -> next;
        }

        free(corrente);
        lista -> contatore -= 1;

    }

    pthread_mutex_unlock(& lista -> mutex);
}

void aggiungiPartita(ListaPartite * lista, Partita * partita) {
        pthread_mutex_lock(& lista -> mutex);

        partita -> next = lista -> head;
        lista -> head = partita;
        lista -> contatore += 1;

        pthread_mutex_unlock(& lista -> mutex);

}

void stampaListaPartite(ListaPartite * lista) {
    Partita * corrente = lista -> head;

    pthread_mutex_lock(& lista -> mutex);

    if (corrente == NULL) {
            printf("La lista delle partite e' vuota\n");  
    } else {
        printf("Lista partite: \n");

        while (corrente != NULL) {
            printf("%d\n", corrente -> id);
            printf("%s - %d\n", corrente -> proprietario -> nome, corrente -> proprietario -> socket);
            printf("%s - %d\n", corrente -> avversario -> nome, corrente -> avversario -> socket);

            corrente = corrente -> next;
        }  
    }

    pthread_mutex_unlock(& lista -> mutex);
}

void rimuoviPartita(ListaPartite * lista, Partita * partita) {

    pthread_mutex_unlock(& lista -> mutex);

    Partita * corrente = lista -> head;
    Partita * precedente = NULL;

    while (corrente != NULL && corrente -> id != partita -> id) {
        precedente = corrente;
        corrente = corrente -> next;
    }

    if (corrente != NULL) {

        if (precedente == NULL) {
            lista -> head = corrente -> next;
        } else {
            precedente -> next = corrente -> next;
        }

        free(corrente);
        lista -> contatore -= 1;

    }

    pthread_mutex_unlock(& lista -> mutex);

}
