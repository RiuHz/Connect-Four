#include "client.h"

ThreadData * creaThreadData(Server * server, int socket) {
    ThreadData * thread = malloc(sizeof(ThreadData));
    
    thread -> server = server;
    thread -> socket = socket;

    return thread;
}

void avviaThreadSocket(Server * server, int socket) {
    pthread_t thread;

    ThreadData * threadData = creaThreadData(server, socket);

    if (pthread_create(& thread, NULL, wrapperThreadSocket, (void *) threadData) != 0) {
        perror("Errore creazione thread");
        exit(1);
    }
}

void * wrapperThreadSocket(void * arg) {
    ThreadData * thread = (ThreadData *) arg;
    
    printf("[Client] [Thread: %lu] Thread per la socket %d avviato correttamente\n", (unsigned long) pthread_self(), thread -> socket);

    Client * client = attendiConnessioneClient(thread -> server, thread -> socket);

    gestisciRichiesteClient(thread -> server, client);

    free(thread);

    return NULL;
}
