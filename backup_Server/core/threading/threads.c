#include "../global/globals.h" 
#include "threads.h"
#include "../handler/handlers.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>

#include <string.h>
#include <sys/socket.h>

#define DIMENSIONE_BUFFER 1024


void associaThreadClient(int nuovoClientConnesso) {
        // Creo il thread
        pthread_t tid;

        int *clientData = malloc(sizeof(int));
        *clientData = nuovoClientConnesso;

        if (pthread_create(&tid, NULL, gestioneClientThread,clientData) != 0) {
                perror("Errore creazione thread");
        }

}

void *gestioneClientThread(void *arg){
        int socketClient = *(int*)arg;
        free(arg); // Rilascio subito la memoria utilizzata e la rendo disponibile immediatamente

        ClientInfo clientInfo;
        clientInfo.socketClient=socketClient;
        memset(clientInfo.nomeClient, 0, 20); // Pulizia di tutti i caratteri

        while(1) 
        {
            MessageHeader intestazionePacchetto = identificaPacchetto(&clientInfo);

            if(intestazionePacchetto.type<=0) break; // client disconnesso/errore

            processaPacchetto(intestazionePacchetto,&clientInfo);

            // fare operazioni varie e introdurre logica di gestione del tipo di messaggi ricevuti

            // SCENARIO 1: CLIENT APPENA CONNESSO - SCOPO: INVIO MESSAGGIO DI BENVENUTO
            // S_Benvenuto pacchetto;
            // pacchetto.tipoMessaggio=S_BENVENUTO;
            // strncpy(pacchetto.messaggioBenvenuto,"Ciao <nomeClient> ti diamo il benvenuto a Forza 4!",sizeof(pacchetto.messaggioBenvenuto));
                    
            //     char risposta[DIMENSIONE_BUFFER];
            //     strcpy(risposta, "Messaggio ricevuto no corrispondenza dal Server!");
            //     sendto(dati->socketServer, risposta, strlen(risposta), 0, (struct sockaddr *)&dati->indirizzoClient, sizeof(dati->indirizzoClient));    

        }

        close(clientInfo.socketClient); // client disconnesso mi chiudo la socket dal server verso quel client

        rimuoviClient(clientInfo.socketClient);

        pthread_exit(NULL);
        
}
