#include "TCPServer.h"
#include "../utils/list.h"
#include "../threading/threads.h"


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


