#include "UDPClient.hpp"
#include <cstring>

namespace lso {

    UDPClient::UDPClient(std::string server_ip, int server_port) {
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

    std::string UDPClient::receiveMessage() {
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
        
        if (n < 0)
            return std::string("");

        buffer[n] = '\0';

        return std::string(buffer);
    }

}
