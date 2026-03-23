#ifndef PARTITA_THREAD_H
#define PARTITA_THREAD_H

#include <pthread.h>

#include "../../controller/partita/partita.h"

#include "../../../model/partita/partita.h"
#include "../../../model/server/server.h"

void avviaThreadPartita(Partita * partita);

void * wrapperThreadPartita(void * arg);

void attendiTerminePartita(Partita * partita);

#endif
