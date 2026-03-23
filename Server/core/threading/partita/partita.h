#ifndef PARTITA_THREAD_H
#define PARTITA_THREAD_H

#include <pthread.h>

#include "../../controller/partita/partita.h"

#include "../../../model/partita/partita.h"
#include "../../../model/server/server.h"

typedef struct ThreadPartitaData {
    Server * server;
    Partita * partita;
} ThreadPartitaData;

ThreadPartitaData * creaThreadPartitaData(Server * sever, Partita * partita);

void avviaThreadPartita(Server * server, Partita * partita);

void * wrapperThreadPartita(void * arg);

void attendiTerminePartita(Partita * partita);

#endif
