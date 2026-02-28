#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "core/threading/broadcast/broadcast.h"
#include "network/shared/protocol.h"
#include "network/tcp/core/TCPServer.h"

int main(void) {

    Server * server = creaSocketServerTCP();

    avviaThreadBroadcast(server);
    avviaServer(server);

    close(server -> socket);

    return 0;
}
