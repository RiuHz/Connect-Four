#include "TCPClient.hpp"

void lso::TCPClient::connectTCPClient() {

    TCPSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (TCPSocket < 0)
        throw std::runtime_error("[Rete] Impossibile creare il socket.");

    struct sockaddr_in serverAddress;
    memset(& serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_ADDRESS, & serverAddress.sin_addr) <= 0)
        throw std::runtime_error("[Rete] Indirizzo IP del server non valido.");

    if (connect(TCPSocket, (struct sockaddr*) & serverAddress, sizeof(serverAddress)) < 0)
        throw std::runtime_error("[Rete] Connessione al server " + std::string(SERVER_ADDRESS) + ":" + std::to_string(SERVER_PORT) + " fallita.");
}

void lso::TCPClient::sendMessage(const Message & message) const {
    uint32_t type = htonl(message.getType());
    uint32_t length = htonl(message.getLength());

    sendData(type);
    sendData(length);

    if (length == 0)
        return;

    std::vector<uint32_t> payload(message.getPayload());

    for (uint32_t & word: payload)
        word = htonl(word);

    sendData(payload, message.getLength());
}

void lso::TCPClient::sendData(const uint32_t data) const {
    size_t bytesSent = 0;
    size_t totalBytes = sizeof(data);
    const uint8_t * buffer = reinterpret_cast<const uint8_t *>(& data);

    while (bytesSent < totalBytes) {
        ssize_t remainingBytes = send(TCPSocket, buffer + bytesSent, totalBytes - bytesSent, 0);

        if (remainingBytes <= 0)
            throw std::runtime_error("[Rete] Impossibile leggere dal buffer TCP.");

        bytesSent += (size_t) remainingBytes;
    }
}

void lso::TCPClient::sendData(const std::vector<uint32_t> & payload, const size_t length) const {
    size_t bytesSent = 0;
    size_t totalBytes = length;
    const uint8_t * buffer = reinterpret_cast<const uint8_t *>(payload.data());

    while (bytesSent < totalBytes) {
        ssize_t remainingBytes = send(TCPSocket, buffer + bytesSent, totalBytes - bytesSent, 0);

        if (remainingBytes <= 0)
            throw std::runtime_error("[Rete] Impossibile scrivere sul buffer TCP.");

        bytesSent += static_cast<size_t>(remainingBytes);
    }
}

const lso::Message lso::TCPClient::receiveMessage() const {
    std::vector<uint32_t> header = receiveData(2);

    MessageType type = static_cast<MessageType>(ntohl(header[0]));
    uint32_t length = ntohl(header[1]);

    if (length == 0)
        return lso::Message(type);

    std::vector<uint32_t> payload = receiveData(length);

    for (uint32_t & word: payload)
        word = ntohl(word);

    return lso::Message(type, payload);
}

const std::vector<uint32_t> lso::TCPClient::receiveData(const uint32_t length) const {
    std::vector<uint32_t> payload(length);

    size_t readBytes = 0;
    size_t totalBytes = sizeof(uint32_t) * payload.size();
    uint8_t * buffer = reinterpret_cast<uint8_t *>(& payload[0]);

    while (readBytes < totalBytes) {
        ssize_t remainingBytes = recv(TCPSocket, buffer + readBytes, length - readBytes, 0);

        if (remainingBytes <= 0)
            throw std::runtime_error("[Rete] Impossibile leggere dal buffer TCP.");

        readBytes += static_cast<size_t>(remainingBytes);
    }

    return payload;
}
