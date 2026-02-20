#ifndef HANDLERS_H
#define HANDLERS_H

#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "request/requests.h"

#include "../../data/client/client.h"

#include "../../network/messaggio/messaggio.h"
#include "../../network/shared/protocol.h"

Messaggio attendiMessaggio(Client * client, MessageType messaggioAtteso);

Messaggio processaMessaggio(MessageHeader header, uint32_t * payload);

void inviaRisposta(Client * client, Messaggio messaggio);

void leggiFlussoDati(Client * client, void * buffer, size_t lunghezza);

#endif