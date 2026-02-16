#include "TCPServer.h"
#include "../shared/contracts.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // per funzioni di conversione tra indirizzo ad ASCII ntoa()
#include <string.h>  // anche per memset


#include <pthread.h>

#define PORTA 5000
#define DIMENSIONE_BUFFER 1024


ListaClient* listaClient = NULL;

int creaSocketServerTCP(){
        int socketServer;
        struct sockaddr_in serverAddress;

        // Creazione del socket TCP
        socketServer = socket(AF_INET, SOCK_STREAM, 0); // (Per docker lasciamo inet, perchè local funziona con i file)
        if (socketServer < 0) {
                perror("Errore nella creazione del socket TCP");
                exit(1);
        }

        // Inizializzo la struttura serverAddress
        memset(&serverAddress,0,sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // (Per docker serve questo, non cambiarlo con quello di loopback)
        serverAddress.sin_port = htons(PORTA);

        // Binding del socket (lego i vari pezzettini)
        if (bind(socketServer, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
                perror("Errore nel binding del socket TCP");
                close(socketServer);
                exit(1);
        }

        if (listen(socketServer, SOMAXCONN) < 0) {
                perror("Errore sull' ascolto dei client da parte del Server");
                exit(1);
        }

        printf("Server TCP pronto sulla porta %d...\n", PORTA);

        return socketServer;
}

void avviaServer(int socketServer){
        struct sockaddr_in indirizzoClient;
        socklen_t lunghezzaIndirizzo;

        printf("Server in ascolto (LOOP)...\n");

        while(1) {
                lunghezzaIndirizzo = sizeof(indirizzoClient);

                int nuovoClient = accept(socketServer,(struct sockaddr *)&indirizzoClient,&lunghezzaIndirizzo);

                if (nuovoClient < 0) {
                        perror("Accept fallita");
                        continue;
                }

                // per debug (da togliere)
                printf("Nuova connessione: socket fd %d, ip %s\n", nuovoClient, inet_ntoa(indirizzoClient.sin_addr));

                // inserisco il nuovoClient valido 
                aggiungiClient(nuovoClient);

                stampaLista(); // only for debug da togliere peffozza

                associaThreadClient(nuovoClient);
                
        } 
}

void associaThreadClient(int nuovoClientConnesso) {
        // Creo il thread
        pthread_t tid;

        int *clientInfo = malloc(sizeof(int));
        *clientInfo = nuovoClientConnesso;

        if (pthread_create(&tid, NULL, gestioneClientThread,clientInfo) != 0) {
                perror("Errore creazione thread");
        }

}

void *gestioneClientThread(void *arg){
        int socketClient = *(int*)arg;
        free(arg); // Rilascio subito la memoria utilizzata e la rendo disponibile immediatamente

        char bufferMessaggi[DIMENSIONE_BUFFER];
        ssize_t byteLetti;

        while(1) 
        {
                byteLetti = recv(socketClient, &bufferMessaggi, sizeof(bufferMessaggi), 0);

                if (byteLetti == 0) {
                        printf("Client disconnesso (Socket %d)\n", socketClient);
                        break; // Usciamo dal loop e cancellazione di quell' elemento dalla lista
                }

                else if (byteLetti < 0) {
                        perror("Errore recv");
                        break;
                }

                // fare operazioni varie e introdurre logica di gestione del tipo di messaggi ricevuti

                // SCENARIO 1: CLIENT APPENA CONNESSO - SCOPO: INVIO MESSAGGIO DI BENVENUTO
                // S_Benvenuto pacchetto;
                // pacchetto.tipoMessaggio=S_BENVENUTO;
                // strncpy(pacchetto.messaggioBenvenuto,"Ciao <nomeClient> ti diamo il benvenuto a Forza 4!",sizeof(pacchetto.messaggioBenvenuto));
                        
                //     char risposta[DIMENSIONE_BUFFER];
                //     strcpy(risposta, "Messaggio ricevuto no corrispondenza dal Server!");
                //     sendto(dati->socketServer, risposta, strlen(risposta), 0, (struct sockaddr *)&dati->indirizzoClient, sizeof(dati->indirizzoClient));    

        }

        close(socketClient); // client disconnesso mi chiudo la socket dal server verso quel client

        // aggiungere rimozione in lista di quello specifico client

        pthread_exit(NULL);
        
}

// Implementazione per le funzioni dedicate alle liste
void aggiungiClient(int nuovoClientConnesso){
        ListaClient *nuovoNodo,*tempNodo;
        nuovoNodo=malloc(sizeof(ListaClient));

        nuovoNodo->socketClient=nuovoClientConnesso;
        nuovoNodo->next=NULL;

        if(listaClient==NULL){
                listaClient=nuovoNodo;
        }
        else
        {
                tempNodo=listaClient;
                nuovoNodo->next=tempNodo;
                listaClient=nuovoNodo;
        }

}

// per debug (da togliere)
void stampaLista(){
        if(listaClient==NULL){
              printf("\n La lista e' vuota\n");  
        }
        else
        {
                printf("\n Lista: ");
                while(listaClient!=NULL)
                {
                        printf("\n %d\n",listaClient->socketClient);
                        listaClient=listaClient->next;
                }  
        }
}
