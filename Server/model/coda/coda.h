#ifndef CODA_H
#define CODA_H

#include <dispatch/dispatch.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

#include "../messaggio/messaggio.h"

typedef struct MessaggioBroadcast {
    Messaggio * messaggio;
    struct MessaggioBroadcast * next;
} MessaggioBroadcast;

typedef struct CodaBroadcast {
    pthread_mutex_t mutex;
    dispatch_semaphore_t semaforo;
    MessaggioBroadcast * head;
    MessaggioBroadcast * tail;
} CodaBroadcast;

MessaggioBroadcast * creaMessaggioBroadcast(Messaggio messaggio);
void cancellaMessaggioBroadcast(MessaggioBroadcast * messaggio);

void accodaMessaggioBroadcast(CodaBroadcast * coda, Messaggio messaggio);
void stampaCodaBroadcast(CodaBroadcast * coda);
void decodaMessaggioBroadcast(CodaBroadcast * coda);

#endif
