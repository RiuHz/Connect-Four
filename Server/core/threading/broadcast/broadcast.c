#include "broadcast.h"

void avviaThreadBroadcast(Server * server) {
    pthread_t thread;

    if (pthread_create(& thread, NULL, wrapperBroadcast, (void *) server) != 0) {
        perror("Errore creazione broadcast");
        exit(1);
    }
}

void * wrapperBroadcast(void * arg) {
    Server * server = (Server *) arg;

    avviaBroadcast(server);

    return NULL;
}
