#include "LoginState.hpp"

void LoginState::onEnter(ClientContext* /*context*/) {
    std::cout << "\n=========================================\n";
    std::cout << "      (: BENVENUTO A CONNECT FOUR :)       \n";
    std::cout << "=========================================\n";
    std::cout << "Inserisci il tuo nome giocatore: ";
}

void LoginState::handleUserInput(ClientContext* context, const std::string& input) {
    if (input.empty() || input.length() < 1) {
        std::cout << "Nome troppo corto. Riprova: ";
        return; // Interrompiamo qui, restando nel LoginState
    }

    context->setPlayerName(input);
    
    std::cout << "\n[Rete] Tentativo di connessione al server in corso ... \n";

    if (context->getNetwork()->connectToServer(SERVER_ADDRESS, SERVER_PORT)) {
        std::cout << "[Rete] Connessione stabilita con successo!\n";
        
        std::string payloadNome = context->getPlayerName();
        payloadNome.resize(NAME_LEN, '\0'); // fix bug che mandava in crash il server SCUS :)

        std::string packet = PacketBuilder::encode(REQ_CONNECT, payloadNome); // questo deve prendere solo i dati e codificarli per l'invio o in alternativa funzioni specifiche (handler per ogni request forse meglio aiut quanto e lungo questo commento )

        context->getNetwork()->sendData(packet);

        // Cambiamo stato, passando al Menu Principale
        context->transitionTo(std::make_unique<MenuState>());
    } else {
        std::cout << "[Rete] Impossibile connettersi al server\n";
        context->stop(); // O interrompiamo tutto o restiamo nello stato di login e dobbiamo ideare una funzione di reset che fa tutto (hard choice => long deployment)
    }

}