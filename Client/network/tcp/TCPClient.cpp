#include "TCPClient.hpp"

// Inizializzo il costruttore per buona pratica del TCPClient
TCPClient::TCPClient() : clientSocket(-1), connected(false) {}

// Distruttore che quando invocato disconnette il client, chiude la socket
TCPClient::~TCPClient() {
    disconnect();
}

bool TCPClient::connectToServer(const std::string& serverIp, uint16_t serverPort) {
    if (connected) return true;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "[Errore di Rete] Impossibile creare il socket.\n";
        return false;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort); 

    if (inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "[Errore di Rete] Indirizzo IP non valido o non supportato.\n";
        close(clientSocket);
        return false;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "[Errore di Rete] Connessione al server " << serverIp << ":" << serverPort << " fallita.\n";
        close(clientSocket);
        return false;
    }

    connected = true;
    return true;
}

void TCPClient::disconnect() {
    if (connected && clientSocket >= 0) {
        close(clientSocket);
        clientSocket = -1;
        connected = false;
        std::cout << "[Rete] Disconnesso dal server.\n";
    }
}

bool TCPClient::isConnected() const {
    return connected;
}

bool TCPClient::sendData(const std::string& data) {
    if (!connected) return false;

    ssize_t bytesSent = send(clientSocket, data.c_str(), data.length(), 0);
    
    if (bytesSent < 0) {
        std::cerr << "[Errore di Rete] Invio dati fallito.\n";
        disconnect(); // Se l'invio fallisce gravemente, probabilmente la connessione è caduta
        return false;
    }
    return true;
}

std::string TCPClient::receiveData() {
    if (!connected) return "";

    std::vector<char> buffer(4096);
    
    // recv è bloccante, finché non arrivano dati
    ssize_t bytesReceived = recv(clientSocket, buffer.data(), buffer.size() - 1, 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // Terminatore di stringa
        return std::string(buffer.data());
    } else if (bytesReceived == 0) {
        std::cout << "[Rete] Il server ha chiuso la connessione.\n";
        disconnect();
    } else {
        std::cerr << "[Errore di Rete] Errore durante la ricezione.\n";
        disconnect();
    }
    return "";
}