#include "client.h"

ThreadClientData * creaThreadClientData(Server * server, int socket) {
    ThreadClientData * thread = malloc(sizeof(ThreadClientData));
    
    thread -> server = server;
    thread -> socket = socket;

    return thread;
}

void avviaThreadSocket(Server * server, int socket) {
    pthread_t thread;

    ThreadClientData * threadData = creaThreadClientData(server, socket);

    if (pthread_create(& thread, NULL, wrapperThreadSocket, (void *) threadData) != 0) {
        perror("Errore creazione thread");
        exit(1);
    }
}

void * wrapperThreadSocket(void * arg) {
    ThreadClientData * thread = (ThreadClientData *) arg;
    
    printf("[Client] [Thread: %lu] Thread per la socket %d avviato correttamente\n", (unsigned long) pthread_self(), thread -> socket);

    Client * client = attendiConnessioneClient(thread -> server, thread -> socket);

    gestisciRichiesteClient(thread -> server, client);

    free(thread);

    return NULL;
}
