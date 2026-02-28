#include "ClientContext.hpp"

ClientContext::ClientContext(std::unique_ptr<State> initialState) : isRunning(true) {
    transitionTo(std::move(initialState));
}

void ClientContext::transitionTo(std::unique_ptr<State> newState) {
    currentState = std::move(newState); 
    if (currentState) {
        currentState->onEnter(this); // Facciamo partire la logica dello stato
    }
}

void ClientContext::stop() {
    if (tcpClient.isConnected()) {
        std::cout << "[RETE] Invio pacchetto di disconnessione al server...\n";
        std::string disconnectPacket = PacketBuilder::encode(REQ_DISCONNECT, "");
        tcpClient.sendData(disconnectPacket);
        
        tcpClient.disconnect(); 
    }

    isRunning = false;
}

void ClientContext::run() {
    std::string input;
    // LOOP finchè siamo in running e il client passa da uno stato all' altro
    while (isRunning) {
        std::getline(std::cin, input); // legge anche gli spazi, cin >> NO!
        if (currentState) {
            currentState->handleUserInput(this, input);
        }
    }
}