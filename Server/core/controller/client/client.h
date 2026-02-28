#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include <stdbool.h>

#include "../../handler/request/requests.h"

#include "../../../model/client/client.h"
#include "../../../model/server/server.h"

#include "../../../network/tcp/core/TCPServer.h"

Client * attendiConnessioneClient(Server * server, int socket);

void gestisciRichiesteClient(Server * server, Client * client);

#endif
