#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../../network/shared/protocol.h"

typedef struct Client {
    pthread_mutex_t mutex;
    int socket;
    char nome[NAME_LEN];
    struct Client * next;
} Client;

Client * creaClient(int socket);

#endif
