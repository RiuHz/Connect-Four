#include "TCPClient.hpp"

namespace lso {

    TCPClient::TCPClient(const std::string server_ip, const unsigned int server_port) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (clientSocket < 0)
            throw std::runtime_error("Cannot create socket...");

        memset(&serverAddress, 0, sizeof(serverAddress));

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(server_port);
        serverAddress.sin_addr.s_addr = inet_addr(server_ip.c_str());

        if (connect(clientSocket, reinterpret_cast<sockaddr *>(& serverAddress), sizeof(serverAddress)) < 0) {
            throw std::runtime_error("Cannot connect to server...");
        }
    }

    void TCPClient::sendMessage(const Message message) const {
        sendMessageHeader(message);

        if (message.getLength() != 0)
            sendMessagePayload(message);
    }

    void TCPClient::sendMessageHeader(const Message & message) const {
        MessageHeader header;

        header.type = htonl(message.getType());
        header.length = htonl(message.getLength());

        size_t totalSent = 0;
        const char* headerPtr = reinterpret_cast<const char *>(& header);

        while (totalSent < sizeof(header)) {
            ssize_t sent = send(
                clientSocket,
                headerPtr + totalSent,
                sizeof(header) - totalSent,
                0
            );

            if (sent <= 0)
                throw std::runtime_error("Failed to send message header");

            totalSent += static_cast<size_t>(sent);
        }
    }

    void TCPClient::sendMessagePayload(const Message & message) const {
        const std::vector<uint32_t> & payload = message.getPayload();

        size_t totalSent = 0;

        const char* payloadPtr = reinterpret_cast<const char *>(payload.data());
        size_t payloadSize = payload.size() * sizeof(uint32_t);

        while (totalSent < payloadSize) {
            ssize_t sent = send(
                clientSocket,
                payloadPtr + totalSent,
                payloadSize - totalSent,
                0
            );
            
            if (sent <= 0)
                throw std::runtime_error("Failed to send message payload");
            
            totalSent += static_cast<size_t>(sent);
        }
    }

    Message TCPClient::receiveMessage() const {

        MessageHeader header = receiveMessageHeader();
        std::vector<uint32_t> payload = receiveMessagePayload(header.length);

        return Message(static_cast<MessageType>(header.type), payload);
    }

    MessageHeader TCPClient::receiveMessageHeader() const {
        MessageHeader header;
        size_t totalReceived = 0;

        while (totalReceived < sizeof(MessageHeader)) {
            ssize_t received = recv(
                clientSocket,
                reinterpret_cast<char*>(& header) + totalReceived,
                sizeof(MessageHeader) - totalReceived,
                0
            );


            if (received <= 0) {
                throw std::runtime_error("Connection closed");
            }

            totalReceived += static_cast<size_t>(received);
        }

        header.type = ntohl(header.type);
        header.length = ntohl(header.length);

        return header;
    }

    std::vector<uint32_t> TCPClient::receiveMessagePayload(const unsigned int length) const {
        std::vector<uint32_t> payload;

        if (length == 0)
            return payload;

        payload.resize(length / sizeof(uint32_t));

        size_t totalReceived = 0;
        char * payloadPtr = reinterpret_cast<char *>(payload.data());

        while (totalReceived < length) {

            ssize_t received = recv(
                clientSocket,
                payloadPtr + totalReceived,
                length - totalReceived,
                0
            );

            if (received <= 0) {
                throw std::runtime_error("Connection closed by server");
            }

            totalReceived += static_cast<size_t>(received);
        }

        for (uint32_t & element : payload) {
            element = ntohl(element);
        }

        return payload;
    }

    bool TCPClient::operator == (const TCPClient & other) const noexcept {
        return clientSocket == other.clientSocket
            && serverAddress.sin_family == other.serverAddress.sin_family
            && serverAddress.sin_port == other.serverAddress.sin_port
            && serverAddress.sin_addr.s_addr == other.serverAddress.sin_addr.s_addr;
    }

}
