#include "Client.hpp"

lso::Client::State::State(lso::Client & client) : context(client) {
    int maxHeight;
    int maxWidth;

    getmaxyx(stdscr, maxHeight, maxWidth);

    outputWindow = std::make_unique<OutputWindow>(maxHeight - 3, maxWidth, 0, 0);
    inputWindow = std::make_unique<InputWindow>(3, maxWidth, maxHeight - 3, 0);
}

// --------------------------------------------------------------------------------

lso::Client::LoginState::LoginState(lso::Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci il tuo nome");    
}

void lso::Client::LoginState::print() const {
    outputWindow -> print(
        "===========================================" "\n"
        "      (: BENVENUTO A CONNECT FOUR :)       " "\n"
        "===========================================" "\n"
    );
}

void lso::Client::LoginState::handleUserInput() const {
    const std::string input = inputWindow -> getInput();

    if (input.empty()) {
        inputWindow -> addTitle("Inserire un nome con almeno un carattere");
        return;
    }

    if (input.length() >= NAME_LEN) {
        inputWindow -> addTitle("Inserire un nome con al massimo " + std::to_string(NAME_LEN - 1) + " caratteri");
        return;
    }

    std::string name(input);
    name.resize(NAME_LEN);

    context.serverConnection -> sendMessage(
        Message(REQ_CONNECT, name)
    );

    context.transitionTo(std::make_unique<MenuState>(context));
}

void lso::Client::LoginState::handleNetworkEvents(const Message & message) const {
    // ! Vuoto
}

// --------------------------------------------------------------------------------

lso::Client::MenuState::MenuState(Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci la tua scelta");
}

void lso::Client::MenuState::print() const {
    outputWindow -> print(
        std::string("MENU PRINCIPALE") + "\n" +
        "1. " + toString.at(MenuOption::CREATE_MATCH) + "\n" +
        "2. " + toString.at(MenuOption::LIST_GAMES) + "\n" +
        "3. " + toString.at(MenuOption::EXIT) + "\n"
    );
}

void lso::Client::MenuState::handleUserInput() const {
    const std::string input = inputWindow -> getInput();

    if (input.empty()) {
        inputWindow -> addTitle("Scelta vuota non supportata");
        return;
    }

    if (! std::all_of(input.begin(), input.end(), ::isdigit)) {
        inputWindow -> addTitle("Scelta non numerica non supportata");
        return;
    }

    const int option = std::stoi(input);

    switch (static_cast<MenuOption>(option)) {
        case MenuOption::CREATE_MATCH:
            // * Invia richiesta REQ_CREATE_GAME
            // * Gestisci risposta

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
            inputWindow -> addTitle("Uscendo...");
        break;
    }

}

void lso::Client::MenuState::handleNetworkEvents(const Message & message) const {
    // ! Vuoto
}

// --------------------------------------------------------------------------------

lso::Client::LobbyState::LobbyState(Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci la tua scelta");
}

void lso::Client::LobbyState::print() const {
    outputWindow -> print(
        std::string("============ Dettagli Partita ============") + "\n" +
        "ID Partita: " + "Num lobby" + "\n" +
        "Proprietario: " + "Nome Proprietario" + "\n" +
        "Avversario: " + "Nome Avversario" + "\n" +
        "\n" +
        "Digita 'esci' per tornare al Menu Principale"
    );

}

void lso::Client::LobbyState::handleUserInput() const {
    // TODO
}

void lso::Client::LobbyState::handleNetworkEvents(const Message & message) const {
    // TODO
}

// --------------------------------------------------------------------------------

lso::Client::InGameState::InGameState(Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci la colonna");
}

void lso::Client::InGameState::print() const {
    // TODO
    // * Quindi andra il print della board, perché siamo in partita
}

void lso::Client::InGameState::handleUserInput() const {
    // TODO
}

void lso::Client::InGameState::handleNetworkEvents(const Message & message) const {
    // TODO
}

// --------------------------------------------------------------------------------

lso::Client::GameListState::GameListState(Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci il numero della lobby");
}

void lso::Client::GameListState::print() const {
    outputWindow -> print(
        std::string("============== Lista Partite ==============") + "\n" +
        "1) Proprietario VS Avversario (In Attesa / In Gioco / Appena Creata / Terminata)" + "\n" +
        "\n" +
        "Digita '0' per tornare la Menu Principale"
    );
}

void lso::Client::GameListState::handleUserInput() const {
    // TODO
}

void lso::Client::GameListState::handleNetworkEvents(const Message & message) const {
    // TODO
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
        state -> print();
        state -> handleUserInput();
    };
}
