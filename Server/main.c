#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <strings.h>
#include <string.h>

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

int creaSocketServerUDP();
void avviaServer(int socketServer);
void associaThreadClient(int socket, struct sockaddr_in addr, char *buffer, ssize_t len);
void *inviaMessaggio(void *arg);

int main()
{   
        int socketServer = creaSocketServerUDP();

        avviaServer(socketServer);

        close(socketServer); // Per sicurezza anche se nin verrà mai raggiunto perchè il server è sempre in ascolto continuamente

        return 0;
}

int creaSocketServerUDP(){
        int socketServer;
        struct sockaddr_in serverAddress;

        // Creazione del socket UDP
        socketServer = socket(AF_INET, SOCK_DGRAM, 0);
        if (socketServer < 0) {
                perror("Errore nella creazione del socket UDP");
                exit(1);
        }

        // Inizializzo la struttura serverAddress
        memset(&serverAddress,0,sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
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

        // Esempio di risposta
        char risposta[DIMENSIONE_BUFFER];
        sprintf(risposta, "Ciao, sono il thread %lu, ho ricevuto il tuo messaggio", (unsigned long)pthread_self());
    
        sendto(dati->socketServer, risposta, strlen(risposta), 0,
           (struct sockaddr *)&dati->indirizzoClient, sizeof(dati->indirizzoClient));
        
        sleep(10); // Dato che ottimizza la memoria cosi usa due thread separati
        
        // Libero tutto
        free(dati);
        pthread_exit(NULL);
}