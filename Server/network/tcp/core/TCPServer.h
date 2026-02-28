#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <pthread.h>

#include "../../../core/threading/client/client.h"

#include "../../../model/messaggio/messaggio.h"
#include "../../../model/server/server.h"

#include "../../shared/protocol.h"

Server * creaSocketServerTCP(void);

void avviaServer(Server * server);

Messaggio attendiMessaggio(Client * client);
void leggiFlussoDati(Client * client, void * buffer, size_t lunghezza);

void inviaMessaggio(Client * client, Messaggio messaggio);
void inviaFlussoDati(Client * client, uint32_t * buffer, size_t dimensione);

#endif
