#include "list.h"
#include "../global/globals.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>



// Implementazione per le funzioni dedicate alle liste
void aggiungiClient(int nuovoClientConnesso){
        ListaClient *nuovoNodo,*tempNodo;
        nuovoNodo=malloc(sizeof(ListaClient));

        nuovoNodo->socketClient=nuovoClientConnesso;
        nuovoNodo->next=NULL;

        pthread_mutex_lock(&mutexListaClient); // blocco gli altri e aggiungo solo io l' elemento

        if(listaClient==NULL){
                listaClient=nuovoNodo;
        }
        else
        {
                tempNodo=listaClient;
                nuovoNodo->next=tempNodo;
                listaClient=nuovoNodo;
        }

        pthread_mutex_unlock(&mutexListaClient); // sblocco gli altri che possono fare operazioni

}

// per debug (da togliere)
void stampaListaClient(){
        ListaClient* corrente=listaClient;

        pthread_mutex_lock(&mutexListaClient); // blocco gli altri e aggiungo solo io l' elemento

        if(corrente==NULL){
              printf("\n La lista dei Client e' vuota\n");  
        }
        else
        {
                printf("\n Lista client: ");
                while(corrente!=NULL)
                {
                        printf("\n %d\n",corrente->socketClient);
                        corrente=corrente->next;
                }  
        }

        pthread_mutex_unlock(&mutexListaClient); // sblocco gli altri che possono fare operazioni

}

void rimuoviClient(int clientDisconnesso){

        pthread_mutex_lock(&mutexListaClient); // blocco l' accesso a tutti gli altri thread

        ListaClient* corrente = listaClient;
        ListaClient* precedente = NULL;

        while(corrente!=NULL && corrente->socketClient != clientDisconnesso)
        {
                precedente=corrente;
                corrente=corrente->next;
        }

        if(corrente != NULL){
                if(precedente==NULL){
                        listaClient= corrente->next; // testa
                } else {
                        precedente->next = corrente->next; // in mezzo o coda
                }
                free(corrente);
        }

        pthread_mutex_unlock(&mutexListaClient); // sblocco l' acceso agli altri thread

}

void aggiungiPartitaAllaLista(Partita partita){
        ListaPartite *nuovoNodo,*tempNodo;
        nuovoNodo=malloc(sizeof(ListaPartite));

        nuovoNodo->partita=partita;
        nuovoNodo->next=NULL;

        pthread_mutex_lock(&mutexListaPartite); // blocco gli altri e aggiungo solo io l' elemento

        if(listaPartite==NULL){
                listaPartite=nuovoNodo;
        }
        else
        {
                tempNodo=listaPartite;
                nuovoNodo->next=tempNodo;
                listaPartite=nuovoNodo;
        }

        pthread_mutex_unlock(&mutexListaPartite); // sblocco gli altri che possono fare operazioni

}

void stampaListaPartite(){
        ListaPartite* corrente=listaPartite;

        pthread_mutex_lock(&mutexListaPartite); // blocco gli altri e aggiungo solo io l' elemento

        if(corrente==NULL){
              printf("\n La lista delle partite e' vuota\n");  
        }
        else
        {
                printf("\n Lista partite: ");
                while(corrente!=NULL)
                {
                        printf("\n %d\n",corrente->partita.id);
                        printf("\n %s\n",corrente->partita.proprietario);
                        printf("\n %s\n",corrente->partita.avversario);
                        printf("\n %d\n",corrente->partita.stato);
                        corrente=corrente->next;
                }  
        }

        pthread_mutex_unlock(&mutexListaPartite); // sblocco gli altri che possono fare operazioni
}

Payload_RES_GAMES_LIST* ottieniListaPartite(size_t *dimensioneStruttura){

        pthread_mutex_lock(&mutexListaPartite); // blocco gli altri 
        pthread_mutex_lock(&mutexNumeroPartita); // blocco gli altri

        // CALCOLO DIMENSIONE TOTALE
        size_t dimensione_totale = sizeof(Payload_RES_GAMES_LIST) + (sizeof(Game) * numeroPartita);
        *dimensioneStruttura = dimensione_totale;

        // ALLOCAZIONE
        Payload_RES_GAMES_LIST *listaPartiteDaInviare = malloc(dimensione_totale);
        listaPartiteDaInviare->numberOfGames = htonl(numeroPartita); 

        ListaPartite* corrente=listaPartite;

        if(corrente==NULL){
              printf("\n La lista delle partite e' vuota\n");  
        }
        else
        {
                while(corrente!=NULL)
                {
                        listaPartiteDaInviare->games->id=corrente->partita.id;
                        strcpy(listaPartiteDaInviare->games->proprietario,corrente->partita.proprietario);
                        strcpy(listaPartiteDaInviare->games->avversario,corrente->partita.avversario);
                        listaPartiteDaInviare->games->stato=corrente->partita.stato;

                        corrente=corrente->next;
                }

        }

        pthread_mutex_unlock(&mutexNumeroPartita); // sblocco gli altri che possono fare operazioni
        pthread_mutex_unlock(&mutexListaPartite); // sblocco gli altri che possono fare operazioni

        return listaPartiteDaInviare;

}