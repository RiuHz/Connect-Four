#include "UDPServer.h"

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

// Struttura dati per il thread necessaria
typedef struct {
    int socketServer;
    struct sockaddr_in indirizzoClient;
    char buffer[DIMENSIONE_BUFFER];
    ssize_t lunghezzaMessaggio;
} ClientInfo;


int creaSocketServerUDP(){
        int socketServer;
        struct sockaddr_in serverAddress;

        // Creazione del socket UDP
        socketServer = socket(AF_INET, SOCK_DGRAM, 0); // (Per docker lasciamo inet, perchè local funziona con i file)
        if (socketServer < 0) {
                perror("Errore nella creazione del socket UDP");
                exit(1);
        }

        // Inizializzo la struttura serverAddress
        memset(&serverAddress,0,sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // (Per docker serve questo, non cambiarlo con quello di loopback)
        serverAddress.sin_port = htons(PORTA);

        // Binding del socket (lego i vari pezzettini)
        if (bind(socketServer, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
                perror("Errore nel binding del socket UDP");
                close(socketServer);
                exit(1);
        }

        printf("Server UDP pronto sulla porta %d...\n", PORTA);

        return socketServer;
}

void avviaServer(int socketServer){
        struct sockaddr_in indirizzoClient;
        socklen_t lunghezzaIndirizzo;
        char bufferMessaggi[DIMENSIONE_BUFFER];
        ssize_t byteLetti;

        printf("Server in ascolto (LOOP)...\n");

        while(1) {
                lunghezzaIndirizzo = sizeof(indirizzoClient);
                
                // Aspetto la ricezione di un messaggio dal client (Bloccante)
                byteLetti = recvfrom(socketServer, bufferMessaggi, DIMENSIONE_BUFFER, 0, 
                        (struct sockaddr*)&indirizzoClient, &lunghezzaIndirizzo);
                
                if (byteLetti > 0) {
                        associaThreadClient(socketServer, indirizzoClient, bufferMessaggi, byteLetti);
                }
        } 
}



void associaThreadClient(int socket, struct sockaddr_in addr, char *buffer, ssize_t len) {
        // Allocazione della struttura dati da passare al thread
        ClientInfo *dati = (ClientInfo *)malloc(sizeof(ClientInfo));
        if (dati == NULL) {
                perror("Errore malloc");
                return;
        }

        // Copio i dati passati alla funzione
        dati->socketServer = socket;
        dati->indirizzoClient = addr;
        dati->lunghezzaMessaggio = len;
        memcpy(dati->buffer, buffer, (size_t)len);

        // Creo il thread
        pthread_t tid;
        if (pthread_create(&tid, NULL, inviaMessaggio, (void *)dati) != 0) {
                perror("Errore creazione thread");
        }

}

void *inviaMessaggio(void *arg) {
        ClientInfo *dati = (ClientInfo *)arg;
        pthread_detach(pthread_self()); // Ripulisce automaticamente i dati alla fine

        dati->buffer[dati->lunghezzaMessaggio] = '\0';
        printf("[Thread %lu] Elaborazione pacchetto da %s\n", 
                (unsigned long)pthread_self(), inet_ntoa(dati->indirizzoClient.sin_addr));

        // INSERIRE LOGICA PER LA GESTIONE DEI MESSAGGI (bozza qui da rivedere e rifattorizzare assolutamente altrimenti esplodo)
        char risposta[DIMENSIONE_BUFFER];

        // SCENARIO 1: CLIENT APPENA CONNESSO - SCOPO: INVIO MESSAGGIO DI BENVENUTO
        if (strncmp(dati->buffer, "Ciao, sono un nuovo Client!", 27) == 0) {
            sprintf(risposta, "Ciao, sono il thread %lu, ho ricevuto il tuo messaggio di saluto. Benvenuto a Forza 4!", (unsigned long)pthread_self());
        }
        else
        {
            strcpy(risposta, "Messaggio ricevuto no corrispondenza dal Server!");
        }        
    
        sendto(dati->socketServer, risposta, strlen(risposta), 0,
           (struct sockaddr *)&dati->indirizzoClient, sizeof(dati->indirizzoClient));
        
        sleep(10); // Per prova, da togliere
        
        // Libero tutto
        free(dati);
        pthread_exit(NULL);
}