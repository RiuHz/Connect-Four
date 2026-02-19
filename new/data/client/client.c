#include "client.h"

Client * creaClient(int socket) {
    Client * client = malloc(sizeof(Client));

    client -> socket = socket;
    memset(client->nome, 0, NAME_LEN);
    client -> next = NULL;

    return client;
}
