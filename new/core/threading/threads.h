#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>

#include "../handler/request/requests.h"

#include "../../data/client/client.h"

#include "../../network/messaggio/messaggio.h"
#include "../../network/tcp/TCPServer.h"

typedef struct ServerData ServerData;

typedef struct ThreadData {
    Client * client;
    ServerData * server;
} ThreadData;

ThreadData * creaThreadData(Client * client, ServerData * sever);

void associaThreadSocket(ServerData * server, int socket);

void * wrapperAssociaThreadClient(void * args);

void associaThreadClient(ServerData * server, Client * client);

#endif
