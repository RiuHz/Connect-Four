#include "Client.hpp"

lso::Client::State::State(lso::Client & client) : context(client) {
    int maxHeight;
    int maxWidth;

    getmaxyx(stdscr, maxHeight, maxWidth);

    outputWindow = std::make_unique<OutputWindow>(maxHeight - 3, maxWidth, 0, 0);
    inputWindow = std::make_unique<InputWindow>(3, maxWidth, maxHeight - 3, 0);
}

void lso::Client::State::handleServerEvents(const Message & message) {
    // TODO Switch con tutti gli eventi in break

    switch (message.getType()) {

        default:
            context.receiveQueue.Enqueue(message);
    }
}

// --------------------------------------------------------------------------------

lso::Client::LoginState::LoginState(lso::Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci il tuo nome");    
}

void lso::Client::LoginState::print() const {
    std::ostringstream stream;

    stream
        << "===========================================" << std::endl
        << "      (: BENVENUTO A CONNECT FOUR :)       " << std::endl
        << "===========================================" << std::endl;

    outputWindow -> print(stream.str());
}

void lso::Client::LoginState::handleUserInput() const {
    std::string name = inputWindow -> getInput();

    if (name.empty()) {
        inputWindow -> addTitle("Inserire un nome con almeno un carattere");
        return;
    }

    if (name.length() >= NAME_LEN) {
        inputWindow -> addTitle("Inserire un nome con al massimo " + std::to_string(NAME_LEN - 1) + " caratteri");
        return;
    }

    name.resize(NAME_LEN);

    context.send(Message(REQ_CONNECT, name));

    context.transitionTo(std::make_unique<MenuState>(context));
}

// --------------------------------------------------------------------------------

lso::Client::MenuState::MenuState(Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci la tua scelta");
}

void lso::Client::MenuState::print() const {
    std::ostringstream stream;

    stream
        << "MENU PRINCIPALE" << std::endl
        << "1. " << MenuOption::CREATE_MATCH << std::endl
        << "2. " << MenuOption::LIST_GAMES << std::endl
        << "3. " << MenuOption::EXIT << std::endl;
    
    outputWindow -> print(stream.str());
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
            context.send(Message(REQ_CREATE_GAME));
            // Message response = context.receive();

            // * Gestisci risposta

            context.transitionTo(std::make_unique<LobbyState>(context));
        break;

        case MenuOption::LIST_GAMES:
            context.send(Message(REQ_GAMES_LIST));

            // * Gestisci cosa succede se chiedo la lista di lobby

            context.transitionTo(std::make_unique<GameListState>(context));
        break;

        case MenuOption::EXIT:
            inputWindow -> addTitle("Disconnessione in corso...");
            context.send(Message(REQ_DISCONNECT));

            context.isRunning = false;
        break;
    }

}

// --------------------------------------------------------------------------------

lso::Client::LobbyState::LobbyState(Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci la tua scelta");
}

void lso::Client::LobbyState::print() const {
    std::ostringstream stream;

    stream
        << "============ Dettagli Partita ============" << std::endl
        << "ID Partita: " <<  "Num lobby" << std::endl
        << "Proprietario: " <<  "Nome Proprietario" << std::endl
        << "Avversario: " <<  "Nome Avversario" << std::endl
        << std::endl
        << "Digita 'esci' per tornare al Menu Principale";
    
    outputWindow -> print(stream.str());
}

void lso::Client::LobbyState::handleUserInput() const {
    // TODO
}

void lso::Client::LobbyState::handleServerEvents(const Message & message) {
    // TODO

    switch (message.getType()) {

        default:
            State::handleServerEvents(message);
    }
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

void lso::Client::InGameState::handleServerEvents(const Message & message) {
    // TODO

    switch (message.getType()) {

        default:
            State::handleServerEvents(message);
    }
}

// --------------------------------------------------------------------------------

lso::Client::GameListState::GameListState(Client & context) : State(context) {
    inputWindow -> addTitle("Inserisci il numero della lobby");
}

void lso::Client::GameListState::print() const {
    std::ostringstream stream;

    stream
        << "============== Lista Partite ==============" << std::endl
        << "1) Proprietario VS Avversario (In Attesa / In Gioco / Appena Creata / Terminata)" << std::endl
        << std::endl
        << "Digita '0' per tornare al Menu Principale";
    
    outputWindow -> print(stream.str());
}

void lso::Client::GameListState::handleUserInput() const {
    // TODO
}

void lso::Client::GameListState::handleServerEvents(const Message & message) {
    // TODO

    switch (message.getType()) {

        default:
            State::handleServerEvents(message);
    }
}

// --------------------------------------------------------------------------------

void lso::Client::handleEventLoop() {
    Message event;

    while (eventQueue.Dequeue(event)) {
        std::lock_guard<std::mutex> lock(stateTransition);

        state -> handleServerEvents(event);
    }
}

void lso::Client::sendLoop() {
    Message message;

    while (sendQueue.Dequeue(message)) {
        serverConnection -> sendMessage(message);
    };
}

void lso::Client::receiveLoop() {
    Message message;

    while (serverConnection -> receiveMessage(message)) {
        eventQueue.Enqueue(message);
    }
}

void lso::Client::transitionTo(std::unique_ptr<State> nextState) {
    std::lock_guard<std::mutex> lock(stateTransition);

    state = std::move(nextState); 
}

void lso::Client::startThreads() {
    senderThread = std::thread(& Client::sendLoop, this);
    eventHandlerThread = std::thread(& Client::handleEventLoop, this);
    receiverThread = std::thread(& Client::receiveLoop, this);
}

void lso::Client::run() {
    isRunning = true;
    state = std::make_unique<LoginState>(*this);

    startThreads();

    while (isRunning) {
        state -> print();
        state -> handleUserInput();
    };

    stop();
}

void lso::Client::stop() {
    sendQueue.Shutdown();
    receiveQueue.Shutdown();
    eventQueue.Shutdown();

    if (senderThread.joinable()) senderThread.join();
    if (eventHandlerThread.joinable()) eventHandlerThread.join();
    if (receiverThread.joinable()) receiverThread.join();
}