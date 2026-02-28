#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include <pthread.h>

#include "../../controller/client/client.h"

#include "../../../model/server/server.h"

typedef struct ThreadData {
    Server * server;
    int socket;
} ThreadData;

ThreadData * creaThreadData(Server * sever, int socket);

void avviaThreadSocket(Server * server, int socket);

void * wrapperThreadSocket(void * arg);

#endif
