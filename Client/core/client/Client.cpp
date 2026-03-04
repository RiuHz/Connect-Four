#include "Client.hpp"

// --------------------------------------------------------------------------------

void lso::Client::LoginState::print() const {
    std::cout
        << "===========================================" << std::endl
        << "      (: BENVENUTO A CONNECT FOUR :)       " << std::endl
        << "===========================================" << std::endl
        << std::endl
        << "Inserisci il tuo nome giocatore" << std::endl;
}

void lso::Client::LoginState::handleUserInput(const std::string & input) const {
    if (input.empty()) {
        Screen::briefDisplay("Inserire un nome con almeno un carattere");
        return;
    }

    if (input.length() >= NAME_LEN) {
        Screen::briefDisplay("Inserire un nome con al massimo " + std::to_string(NAME_LEN - 1) + " caratteri");
        return;
    }

    context.serverConnection -> sendMessage(
        Message(REQ_CONNECT, input)
    );

    context.transitionTo((std::make_unique<MenuState>(context)));
}

void lso::Client::LoginState::handleNetworkEvents(const Message & message) const {
    // ! BHO
}

// --------------------------------------------------------------------------------

void lso::Client::MenuState::print() const {
    std::cout
        << "=== MENU PRINCIPALE ===" << std::endl
        << "1. " << MenuOption::CREATE_MATCH << std::endl
        << "2. " << MenuOption::LIST_GAMES << std::endl
        << "3. " << MenuOption::EXIT << std::endl
        << std::endl
        << "Inserisci la tua scelta" << std::endl;
}

void lso::Client::MenuState::handleUserInput(const std::string & input) const {
    if (input.empty()) {
        Screen::briefDisplay("Scelta vuota non supportata");
        return;
    }

    if (! std::all_of(input.begin(), input.end(), ::isdigit)) {
        Screen::briefDisplay("Scelta numerica non supportata");
        return;
    }

    const int option = std::stoi(input);

    switch (static_cast<MenuOption>(option)) {
        case MenuOption::CREATE_MATCH:
            // * Invia richiesta REQ_CREATE_GAME
            // * Gestisci richiesta

            context.transitionTo(std::make_unique<LobbyState>(context));
        break;

        case MenuOption::LIST_GAMES:
            // * Gestisci cosa succede se chiedo la lista di lobby

            context.transitionTo(std::make_unique<GameListState>(context));
        break;

        case MenuOption::EXIT:
            context.serverConnection -> sendMessage(
                Message(REQ_DISCONNECT)
            );

            context.isRunning = false;
            Screen::briefDisplay("Uscendo...");
        break;

        default:
            Screen::briefDisplay("Scelta numerica non supportata");
    }

}

void lso::Client::MenuState::handleNetworkEvents(const Message & message) const {
    // ! BHO
}

// --------------------------------------------------------------------------------

void lso::Client::LobbyState::print() const {
    // ! Devono diventare attr del Lobby Model

    std::cout
        << "============ Dettagli Partita ============" << std::endl
        << "ID Partita : " << 1 << std::endl
        << "Proprietario : " << " <NomeProprietario> " << std::endl
        << "Avversario : " << " < In attesa di un giocatore > " << std::endl
        << std::endl
        << "Scrivi 'esci' per tornare al Menu Principale." << std::endl;
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
    std::cout 
    << "============== Lista Partite ==============" << std::endl;

    // For lobby in listaLobby stampa lobby;
    // * 1) Mario VS ... (In Attesa / In Gioco / Appena Creata / Terminata)
    // * 1) Mario VS ... In Attesa / In Gioco / Appena Creata / Terminata
    // * 1) Mario VS ... In Attesa / In Gioco / Appena Creata / Terminata
    // * 1) Mario VS ... In Attesa / In Gioco / Appena Creata / Terminata

    std::cout
        << "Digita 0 per tornare al Menu Principale." << std::endl
        << "Inserisci il numero della lobby" << std::endl;
}

void lso::Client::GameListState::handleUserInput(const std::string & input) const {

}

void lso::Client::GameListState::handleNetworkEvents(const Message & message) const {

}

// --------------------------------------------------------------------------------

void lso::Client::setup() {
    // * Thread per gestione eventi dal server

    serverConnection = std::make_unique<TCPClient>();
    state = std::make_unique<LoginState>(*this);
    isRunning = true;
}

void lso::Client::run() {
    setup();

    std::string input;

    while (isRunning) {
        Screen::clear();

        state -> print();
        
        std::cout << "> ";
        std::cin >> input;

        state -> handleUserInput(input);
    };
}
