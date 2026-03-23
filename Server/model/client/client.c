#include "client.h"

Client * creaClient(int socket) {
    Client * client = malloc(sizeof(Client));

    pthread_mutex_init(& client -> mutex, __nonnull);

    client -> socket = socket;
    memset(client->nome, 0, NAME_LEN);
    client -> next = NULL;

    return client;
}
