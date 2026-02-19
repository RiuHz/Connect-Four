#include "threads.h"

void associaThreadConnessione(int socket) {
    pthread_t tid;

    Client * client = creaClient(socket);

    Messaggio messaggio = attendiMessaggio(client, REQ_CONNECT);
    strcpy(client -> nome, messaggio.payload);

    if (pthread_create(&tid, NULL, & gestioneConnessioneThread, client) != 0) {
        perror("Errore creazione thread");
        exit(1);
    }
}

void gestioneConnessioneThread(Client * client) {

    while (true) {
       // Leggo flusso dati con header
       // In caso leggo payload
       // Processo il messaggio
       // Agisco
    }

    close(socketClient);

    rimuoviClient(socketClient);

    pthread_exit(NULL);
}

// C1 -> T1 -> P <- T2 <- C2
