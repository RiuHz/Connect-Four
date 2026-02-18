#include "globals.h"

// Inizializzazioni
pthread_mutex_t mutexListaClient = PTHREAD_MUTEX_INITIALIZER; 
ListaClient* listaClient = NULL;

pthread_mutex_t mutexListaPartite = PTHREAD_MUTEX_INITIALIZER; 
ListaPartite* listaPartite = NULL;

pthread_mutex_t mutexNumeroPartita = PTHREAD_MUTEX_INITIALIZER;
uint32_t numeroPartita = 0;

uint32_t ottieniNuovoIdentificativoPartita(){
        pthread_mutex_lock(&mutexNumeroPartita); // blocco gli altri e aggiungo solo io l' elemento
        numeroPartita++;
        pthread_mutex_unlock(&mutexNumeroPartita); // sblocco gli altri che possono fare operazioni
        return numeroPartita;
}


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