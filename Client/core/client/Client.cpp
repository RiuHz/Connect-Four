#include "Client.hpp"

// --------------------------------------------------------------------------------

void lso::Client::LoginState::print() const {
    std::cout
        << "===========================================" << std::endl
        << "      (: BENVENUTO A CONNECT FOUR :)       " << std::endl
        << "===========================================" << std::endl
        << std::endl
        << "Inserisci il tuo nome giocatore";
}

void lso::Client::LoginState::handleUserInput(const std::string & input) const {

}

void lso::Client::LoginState::handleNetworkEvents(const Message & message) const {

}

// --------------------------------------------------------------------------------

void lso::Client::MenuState::print() const {
    std::cout
        << "=== MENU PRINCIPALE ===" << std::endl
        << "1. " << MenuOption::CREATE_MATCH << std::endl
        << "2. " << MenuOption::LIST_GAMES << std::endl
        << "3. " << MenuOption::EXIT << std::endl
        << std::endl
        << "Inserisci la tua scelta";
}

void lso::Client::MenuState::handleUserInput(const std::string & input) const {

}

void lso::Client::MenuState::handleNetworkEvents(const Message & message) const {

}

// --------------------------------------------------------------------------------

void lso::Client::LobbyState::print() const {

}

void lso::Client::LobbyState::handleUserInput(const std::string & input) const {

}

void lso::Client::LobbyState::handleNetworkEvents(const Message & message) const {

}

// --------------------------------------------------------------------------------

void lso::Client::InGameState::print() const {
    // * Quindi andra il print della board, perché siamo in partita
}

void lso::Client::InGameState::handleUserInput(const std::string & input) const {

}

void lso::Client::InGameState::handleNetworkEvents(const Message & message) const {

}

// --------------------------------------------------------------------------------

void lso::Client::GameListState::print() const {

}

void lso::Client::GameListState::handleUserInput(const std::string & input) const {

}

void lso::Client::GameListState::handleNetworkEvents(const Message & message) const {

}

// --------------------------------------------------------------------------------

void lso::Client::run() const {

}

void lso::Client::LoginState::print() const {
    std::cout << std::endl
    << "=========================================" << std::endl 
    << "     (: BENVENUTO A CONNECT FOUR :)      " << std::endl
    << "=========================================" << std::endl
    << "Inserisci il tuo nome giocatore: ";
}

void lso::Client::MenuState::print() const {
    std::cout << std::endl
    << "=====  MENU PRINCIPALE =====" << std::endl 
    << "1. Crea partita " << std::endl
    << "2. Visualizza lista partite " << std::endl
    << "3. Esci dal gioco " << std::endl
    << "Scelta: ";
}

void lso::Client::LobbyState::print() const {
   /* 
        No stampe statiche? 
        Spostiamo tutto su onEnter che stampa e fa le effettive richieste
   */
}

void lso::Client::LobbyState::onEnter() const {
    std::cout << "\n[REQUEST] Invio della richiesta di creazione partita... \n";

    // Invio effettivamente la richiesta

    std::cout << "\n[REQUEST] Richiesta inviata, in attesa della richiesta di creazione partita... \n";

    // Attendo la risposta dal server che la partita è stata effettivamente creata

    std::cout << "[RESPONSE] Risposta ricevuta correttamente !\n";

    // Una volta ricevuta la risposta come la elaboro?

    // Creo un oggetto di tipo game e una funzione di supporto che mi processa i dati?

    // Stampiamo i dettagli del match creato
    std::cout << 
    std::endl << "=== DETTAGLI PARTITA CREATA ===" << std::endl
    << "ID Partita : " << 1 << std::endl
    << "Proprietario : " << " <NomeProprietario> " << std::endl
    << "Avversario : " << " < In attesa di un giocatore > " << std::endl
    << "Stato : " << " < GAME_WAITING > " << std::endl
    <<" === FINE DETTAGLI PARTITA === " << std::endl;

    std::cout << "Scrivi 'esci' per tornare al Menu Principale." << std::endl;

}

void lso::Client::GameListState::print() const {
    std::cout << 
    std::endl << "=== LISTA PARTITE GLOBALI ===" << std::endl
    << "ID | PROPRIETARIO | AVVERSARIO | STATO " << std::endl
    << " 1 | Mario        | ...        | in attesa... " << std::endl
    << " 2 | Luigi        | Lucia      | in gioco " << std::endl
    << " 3 | Paolo        | ...        | in attesa... " << std::endl
    <<" === FINE LISTA PARTITE GLOBALI === " << std::endl;

    std::cout << 
    std::endl << "=== LISTA NOTIFICA NUOVO MATCH (stampa da omettere) ===" << std::endl
    << " *NUOVA PARTITA CREATA* Sfida Luigi, digita 4 per unirti alla partita " << std::endl
    << " *NUOVA PARTITA CREATA* Sfida Simona, digita 5 per unirti alla partita " << std::endl;

    std::cout << "Scrivi 'esci' per tornare al Menu Principale." << std::endl;

}

