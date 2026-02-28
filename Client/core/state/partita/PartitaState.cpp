#include "PartitaState.hpp"

void PartitaState::onEnter(ClientContext* context) {
    std::cout << "\n[REQUEST] Invio della richiesta di creazione partita... \n";
    std::string packet = PacketBuilder::encode(REQ_CREATE_GAME, "");

    context->getNetwork()->sendData(packet);
    std::cout << "\n[REQUEST] Richiesta inviata, in attesa della richiesta di creazione partita... \n";

    // Attendiamo la risposta del server  (receiveData è bloccante, per favore usiamo i thread qui altrimenti mi ammazzo)
    std::string rawResponse = context->getNetwork()->receiveData();

    // Passiamo i byte grezzi ricevuti dal server al decodificatore
    ParsedPacket response = PacketBuilder::decode(rawResponse);

    if (response.isValid) {
        std::cout << "[RESPONSE] Risposta ricevuta correttamente !\n";
        if (response.type == MessageType::RES_CREATE_GAME) {
            // Controllo di sicurezza: il payload è grande abbastanza per contenere la struct?
            if (response.payload.length() >= sizeof(Game)) {
                
                Game gameInfo;
                
                // Copiamo tutti i byte dal payload di tipo stringa alla nostra struct
                std::memcpy(&gameInfo, response.payload.data(), sizeof(Game));
                
                // Convertiamo i numeri dalla rete all' host voglio esplodere
                uint32_t idGame = ntohl(gameInfo.id);
                uint32_t statoGame = ntohl(gameInfo.stato);
                
                // Stampiamo i risultati a video!
                std::cout << "\n=== DETTAGLI PARTITA CREATA ===\n";
                std::cout << "ID Partita : " << idGame << "\n";
                std::cout << "Proprietario   : " << gameInfo.proprietario << "\n";
                std::cout << "Avversario : " << gameInfo.avversario << "\n";
                std::cout << "Stato      : " << statoGame << "\n";
                std::cout << "==============================\n\n";
            }
        }
        else
        {
            std::cout << "[RESPONSE] Risposta ricevuta correttamente, ma diversa da quella che ci si aspettava :( !\n";
        }

    } else {
        std::cout << "[RESPONSE] Errore di rete: ricevuto un pacchetto corrotto o incompleto.\n";
    }

    std::cout << "Scrivi 'esci' per tornare al Menu Principale.\n> ";
}

void PartitaState::handleUserInput(ClientContext* context, const std::string& input) {
    if (input == "esci") {
        context->transitionTo(std::make_unique<MenuState>());
    } else {
        std::cout << "Hai fatto una mossa: " << input << "\n> ";
    }
}