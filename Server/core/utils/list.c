#include "list.h"
#include "../global/globals.h" 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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
void stampaLista(){
        ListaClient* corrente=listaClient;

        pthread_mutex_lock(&mutexListaClient); // blocco gli altri e aggiungo solo io l' elemento

        if(corrente==NULL){
              printf("\n La lista e' vuota\n");  
        }
        else
        {
                printf("\n Lista: ");
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