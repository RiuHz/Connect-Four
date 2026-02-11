#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 5000


int main()
{   
        char buffer[100];
        char *message = "Hello Client";
        int listenfd;
        socklen_t len;
        struct sockaddr_in servaddr, cliaddr;
        bzero(&servaddr, sizeof(servaddr)); // Pulisce la struttura impostando tutti i byte a zero 
        printf("Server inizializzato\n");

        // Create a UDP Socket
        listenfd = socket(AF_INET, SOCK_DGRAM, 0); 
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long, converte l'indirizzo IP in formato binario e lo assegna alla struttura servaddr
        servaddr.sin_port = htons(PORT); // host to network short, converte il numero di porta in formato binario e lo assegna alla struttura servaddr
        servaddr.sin_family = AF_INET; 
        printf("Socket UDP creata con successo\n");

        // bind server address to socket descriptor
        bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); // Costruisce la vera e propria socket che poi sarà utilizzata (lega i vari pezzi)
        printf("Binding Socket effettuato con successo\n");
        printf("Server in esecuzione...\n");

        /* Esempio di ricezione ed invio del messaggio (da cambiare) */

        //receive the datagram
        len = sizeof(cliaddr);
        ssize_t n = recvfrom(listenfd, buffer, sizeof(buffer),
                0, (struct sockaddr*)&cliaddr,&len); //receive message from server
        if (n > 0) {
        buffer[n] = '\0';
        puts(buffer);
        } 
        else {
        perror("Errore in ricezione\n");
        }
                
        // send the response
        sendto(listenfd, message, strlen(message), 0,
                (struct sockaddr*)&cliaddr, sizeof(cliaddr));
}