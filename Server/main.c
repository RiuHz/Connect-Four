#include <unistd.h>

#include "core/network/UDPServer.h"

int main()
{   
        int socketServer = creaSocketServerUDP();

        avviaServer(socketServer);

        close(socketServer); // Per sicurezza anche se nin verrà mai raggiunto perchè il server è sempre in ascolto continuamente

        return 0;
}

