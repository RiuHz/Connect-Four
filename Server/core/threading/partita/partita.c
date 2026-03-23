#include "partita.h"

ThreadPartitaData * creaThreadPartitaData(Server * server, Partita * partita) {
    ThreadPartitaData * thread = malloc(sizeof(ThreadPartitaData));
    
    thread -> server = server;
    thread -> partita = partita;

    return thread;
}

void avviaThreadPartita(Server * server, Partita * partita) {
    pthread_t thread;

    ThreadPartitaData * threadData = creaThreadPartitaData(server, partita);

    if (pthread_create(& thread, NULL, wrapperThreadPartita, (void *) threadData) != 0) {
        perror("Errore creazione thread partita");
        exit(1);
    }

    partita -> thread = thread;
}

void * wrapperThreadPartita(void * arg) {
    ThreadPartitaData * thread = (ThreadPartitaData *) arg;
    
    printf("[Partita] [Thread: %lu] Thread per la partita %d avviato correttamente\n", (unsigned long) pthread_self(), thread -> partita -> id);

    gestisciPartita(thread -> server, thread -> partita);

    free(thread);

    return NULL;
}

void attendiTerminePartita(Partita * partita) {
    if (pthread_join(partita -> thread, NULL) != 0) {
        printf("Errore nel join del thread\n");
        exit(1);
    }
}
