#include "partita.h"

void avviaThreadPartita(Partita * partita) {
    pthread_t thread;

    if (pthread_create(& thread, NULL, wrapperThreadPartita, (void *) partita) != 0) {
        perror("Errore creazione thread partita");
        exit(1);
    }

    partita -> thread = thread;
}

void * wrapperThreadPartita(void * arg) {
    Partita * partita = (Partita *) arg;
    
    printf("[Partita] [Thread: %lu] Thread per la partita %d avviato correttamente\n", (unsigned long) pthread_self(), partita -> id);

    gestisciPartita(partita);

    return NULL;
}

void attendiTerminePartita(Partita * partita) {
    if (pthread_join(partita -> thread, NULL) != 0) {
        printf("Errore nel join del thread\n");
        exit(1);
    }
}
