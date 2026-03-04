#include "TCPServer.h"

Server * creaSocketServerTCP(void) {
    Server * server = malloc(sizeof(Server));

    server -> socket = socket(AF_INET, SOCK_STREAM, 0);

    impostaParametriServer(server);
    inizializzaListeServer(server);
    
    if (server ->socket < 0) {
        perror("Errore nella creazione del socket TCP");
        exit(1);
    }

    if (bind(server -> socket, (struct sockaddr*) & server -> address, sizeof(server -> address)) < 0) {
        perror("Errore nel binding del socket TCP");
        close(server -> socket);
        exit(1);
    }

    if (listen(server -> socket, SOMAXCONN) < 0) {
        perror("Errore sull' ascolto dei client da parte del Server");
        exit(1);
    }

    printf("[Server] [Thread: %lu] Server avviato sulla porta %d...\n", (unsigned long) pthread_self(), SERVER_PORT);

    return server;
}

void avviaServer(Server * server) {
    struct sockaddr_in indirizzo;

    printf("[Server] [Thread: %lu] Server in ascolto sulla porta %d...\n", (unsigned long) pthread_self(), SERVER_PORT);

    while (true) {
        socklen_t lunghezza = sizeof(indirizzo);

        int socket = accept(server -> socket, (struct sockaddr *) &indirizzo, &lunghezza);

        if (socket < 0) {
            perror("Accept fallita");
            continue;
        }

        printf("[Server] [Thread: %lu] Nuova connessione da ip %s assegnata al socket %d\n", (unsigned long) pthread_self(), inet_ntoa(indirizzo.sin_addr), socket);

        avviaThreadSocket(server, socket);
    } 
}

Messaggio attendiMessaggio(Client * client) {
    MessageHeader header;
    uint32_t * buffer = NULL;

    leggiFlussoDati(client, &header, sizeof(header));

    header.type = ntohl(header.type);
    header.length = ntohl(header.length);

    if (header.length > 0) {
        buffer = malloc(header.length);
        leggiFlussoDati(client, buffer, header.length);
    }

    return creaMessaggio(header.type, header.length, buffer);
}

void leggiFlussoDati(Client * client, void * buffer, size_t lunghezza) {
    size_t bytesLetti = 0;
    char * ptr = (char *) buffer;

    while (bytesLetti < lunghezza) {
        ssize_t byteRimanenti = recv(client -> socket, ptr + bytesLetti, lunghezza - bytesLetti, 0);
        
        if (byteRimanenti <= 0) {
            fprintf(
                stderr,
                "Impossibile leggere dal buffer TCP del thread %lu (%s)",
                (unsigned long) pthread_self(),
                client -> nome
            );
            exit(1);
        }
        
        bytesLetti += (size_t) byteRimanenti;
    }
}

void inviaMessaggio(Client * client, Messaggio messaggio) {
    uint32_t tipo = messaggio.header.type;
    uint32_t dimensione = messaggio.header.length;
    uint32_t * payload = messaggio.payload;

    inviaFlussoDati(client, & tipo, sizeof(uint32_t));
    inviaFlussoDati(client, & dimensione, sizeof(uint32_t));
    inviaFlussoDati(client, payload, dimensione);
}

void inviaFlussoDati(Client * client, uint32_t * buffer, size_t dimensione) {
    size_t byteInviati = 0;

    while (byteInviati < dimensione) {
        ssize_t byteRimanenti = send(client -> socket, buffer + byteInviati, dimensione - byteInviati, 0);

        if (byteRimanenti <= 0) {
            fprintf(
                stderr,
                "Impossibile leggere dal buffer TCP del thread %lu (%s)",
                (unsigned long) pthread_self(),
                client -> nome
            );
            exit(1);
        }

        byteInviati += (size_t) byteRimanenti;
    }
}
