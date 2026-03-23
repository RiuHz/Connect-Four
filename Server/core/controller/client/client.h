#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include <stdbool.h>

#include "../../threading/partita/partita.h"

#include "../../handler/event/events.h"
#include "../../handler/request/requests.h"
#include "../../handler/response/responses.h"

#include "../../../model/client/client.h"
#include "../../../model/server/server.h"

#include "../../../network/tcp/server/TCPServer.h"

Client * attendiConnessioneClient(Server * server, int socket);

void gestisciRichiesteClient(Server * server, Client * client);

#endif
