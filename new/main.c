#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "network/shared/protocol.h"
#include "network/tcp/TCPServer.h"

int main(void) {

    ServerData * server = creaSocketServerTCP();

    avviaServer(server);

    close(server -> socket);

    return 0;
}
