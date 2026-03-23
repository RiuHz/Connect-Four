#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include <pthread.h>

#include "../../controller/client/client.h"

#include "../../../model/server/server.h"

typedef struct ThreadClientData {
    Server * server;
    int socket;
} ThreadClientData;

ThreadClientData * creaThreadClientData(Server * sever, int socket);

void avviaThreadSocket(Server * server, int socket);

void * wrapperThreadSocket(void * arg);

#endif
