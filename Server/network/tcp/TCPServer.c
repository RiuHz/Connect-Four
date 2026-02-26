#include "TCPServer.h"

ServerData * creaSocketServerTCP(void) {
    ServerData * server = malloc(sizeof(ServerData));

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

    printf("[Thread: %lu] Server avviato sulla porta %d...\n", (unsigned long) pthread_self(), SERVER_PORT);

    return server;
}

void impostaParametriServer(ServerData * server) {
    memset(& server -> address, 0, sizeof(server -> address));
    server -> address.sin_family = AF_INET;
    server -> address.sin_addr.s_addr = htonl(INADDR_ANY);
    server -> address.sin_port = htons(SERVER_PORT);
}

void inizializzaListeServer(ServerData * server) {
    server -> listaClient = malloc(sizeof(ListaClient));
    pthread_mutex_init(& server -> listaClient -> mutex, NULL);
    server -> listaClient -> head = NULL;

    server -> listaPartite = malloc(sizeof(ListaPartite));
    pthread_mutex_init(& server -> listaPartite -> mutex, NULL);
    server -> listaPartite -> head = NULL;
}

void avviaServer(ServerData * server) {
    struct sockaddr_in indirizzo;

    printf("[Thread: %lu] Server in ascolto sulla porta %d...\n", (unsigned long) pthread_self(), SERVER_PORT);

    while (true) {
        socklen_t lunghezza = sizeof(indirizzo);

        int socket = accept(server -> socket, (struct sockaddr *) &indirizzo, &lunghezza);

        if (socket < 0) {
            perror("Accept fallita");
            continue;
        }

        printf("[Thread: %lu] Nuova connessione da ip %s assegnata al socket %d\n", (unsigned long) pthread_self(), inet_ntoa(indirizzo.sin_addr), socket);

        associaThreadSocket(server, socket);
    } 
}

void inviaBroadcast(ServerData * server, Messaggio messaggio) {

    printf("[Thread: %lu] Invio del messaggio in broadcast\n", (unsigned long) pthread_self());
    
    pthread_mutex_lock(& server -> listaClient -> mutex); 

    Client * client = server -> listaClient -> head;
    
    while (client != NULL) {
        inviaMessaggio(client, messaggio);

        client = client -> next;
    }

    pthread_mutex_unlock(& server -> listaClient -> mutex);
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

    return creaMessaggio(header.type, buffer);
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
    uint32_t tipo = messaggio.tipo;
    uint32_t lunghezza = sizeof(messaggio.payload);
    uint32_t * payload = messaggio.payload;

    inviaFlussoDati(client, & tipo, sizeof(uint32_t));
    inviaFlussoDati(client, & lunghezza, sizeof(uint32_t));
    inviaFlussoDati(client, payload, sizeof(messaggio.payload));
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
