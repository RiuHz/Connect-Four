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

bool lso::TCPClient::receiveMessage(Message & message) const {
    std::vector<uint32_t> header;
    std::vector<uint32_t> payload;
    
    if (! receiveData(header, 2))
        return false;

    MessageType type = static_cast<MessageType>(ntohl(header[0]));
    uint32_t length = ntohl(header[1]);

    message = Message(type);

    if (length == 0)
        return true;

    if (! receiveData(payload, length / sizeof(uint32_t)))
        return false;

    for (uint32_t & word: payload)
        word = ntohl(word);

    message = Message(type, payload);
    
    return true; 
}

bool lso::TCPClient::receiveData(std::vector<uint32_t> & payload, const uint32_t length) const {
    payload.resize(length);

    size_t readBytes = 0;
    size_t totalBytes = payload.size() * sizeof(uint32_t);
    uint8_t * buffer = reinterpret_cast<uint8_t *>(& payload[0]);
    
    while (readBytes < totalBytes) {
        ssize_t remainingBytes = recv(TCPSocket, buffer + readBytes, totalBytes - readBytes, 0);
        
        if (remainingBytes <= 0)
            return false;
        
        readBytes += static_cast<size_t>(remainingBytes);
    }

    return true;
}
