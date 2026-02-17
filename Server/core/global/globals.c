#include "globals.h"

// Inizializzazioni
pthread_mutex_t mutexListaClient = PTHREAD_MUTEX_INITIALIZER; 
ListaClient* listaClient = NULL;

pthread_mutex_t mutexListaPartite = PTHREAD_MUTEX_INITIALIZER; 
ListaPartite* listaPartite = NULL;

        // Game p1;
        // p1.id=1;
        // strcpy(p1.proprietario,"Mario");
        // strcpy(p1.avversario,"");
        // p1.stato=1u;

        // aggiungiPartitaAllaLista(p1);

        // p1.id=2;
        // strcpy(p1.proprietario,"Nicola");
        // strcpy(p1.avversario,"Maria");
        // p1.stato=2;

        // aggiungiPartitaAllaLista(p1);

        // stampaListaPartite();