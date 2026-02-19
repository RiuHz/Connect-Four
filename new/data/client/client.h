#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>

#include "../../network/shared/protocol.h"

typedef struct Client {
    int socket;
    char nome[NAME_LEN];
    Client * next;
} Client;

Client * creaClient(int socket);

#endif
