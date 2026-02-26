#include <unistd.h>

#include "core/network/TCPServer.h"

int main()
{   
        int socketServer = creaSocketServerTCP();

        avviaServer(socketServer);

        close(socketServer); // Per sicurezza anche se nin verrà mai raggiunto perchè il server è sempre in ascolto continuamente

        return 0;
}

