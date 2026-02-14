#include "UDPClient.hpp"
#include "../../../Server/core/shared/contracts.h"

#include <iostream>
#include <cstring>
#include <arpa/inet.h>

#define MAXLINE 1024

namespace lso {

    UDPClient::UDPClient(std::string server_ip, __uint16_t server_port) {
        clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

        if (clientSocket < 0)
            throw std::runtime_error("Cannot create socket...");

        memset(&serverAddress, 0, sizeof(serverAddress));

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(server_port);
        serverAddress.sin_addr.s_addr = inet_addr(server_ip.c_str());
    }

    UDPClient::~UDPClient() { close(clientSocket); }

    void UDPClient::sendMessage(std::string message) {
        sendto(
            clientSocket,
            message.c_str(),
            message.length(),
            MSG_WAITALL,
            (const struct sockaddr *) &serverAddress,
            sizeof(serverAddress)
        );
    }

    void UDPClient::receiveMessage() {
        char buffer[MAXLINE];

        socklen_t socketLength = sizeof(serverAddress);

        ssize_t n = recvfrom(
            clientSocket,
            buffer,
            MAXLINE,
            MSG_WAITALL,
            (struct sockaddr *) &serverAddress,
            &socketLength
        );

        if (n < 0) {
            std::cout << "Risposta dal Server C: " << "Non ho letto niente" << std::endl;
        }
        else{
            S_Benvenuto* pacchetto = reinterpret_cast<S_Benvenuto*>(buffer);

            if (pacchetto->tipoMessaggio == S_BENVENUTO) {
                std::cout << pacchetto->messaggioBenvenuto << std::endl; 
            }
        }

        //buffer[n] = '\0';

    }

}
