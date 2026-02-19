#include "TCPServer.h"

ServerData * creaSocketServerTCP() {
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

    printf("Server TCP pronto sulla porta %d...\n", SERVER_PORT);

    return server;
}

void impostaParametriServer(ServerData * server) {
    memset(& server -> address, 0, sizeof(server -> address));
    server -> address.sin_family = AF_INET;
    server -> address.sin_addr.s_addr = htonl(INADDR_ANY);
    server -> address.sin_port = htons(SERVER_PORT);
}

void inizializzaListeServer(ServerData * server) {
    pthread_mutex_init(& server -> listaClient.mutex, NULL);
    server -> listaClient.head = NULL;

    pthread_mutex_init(& server -> listaPartite.mutex, NULL);
    server -> listaPartite.head = NULL;
}

void avviaServer(ServerData * server) {
    struct sockaddr_in indirizzo;

    printf("Server in ascolto (LOOP)...\n");

    while (true) {
        socklen_t lunghezza = sizeof(indirizzo);

        int socket = accept(server -> socket, (struct sockaddr *) &indirizzo, &lunghezza);

        if (socket < 0) {
            perror("Accept fallita");
            continue;
        }

        printf("Nuova connessione: socket fd %d, ip %s\n", socket, inet_ntoa(indirizzo.sin_addr));

        associaThreadConnessione(socket);
    } 
}

void inviaBroadcast(ServerData * server, void * datiPacchetto, size_t dimensioneTotale) {
    
    pthread_mutex_lock(& server -> listaClient.mutex); 

    Client * client = server -> listaClient.head;
    
    while (client != NULL) {
        ssize_t byteInviati = send(client -> socket, datiPacchetto, dimensioneTotale, 0);
        
        if (byteInviati < 0) {
            fprintf(stderr, "Error nell invio broadcast al client %d - %s", client -> socket, client -> nome);
        }

        client = client -> next;
    }

    pthread_mutex_unlock(& server -> listaClient.mutex);
}
