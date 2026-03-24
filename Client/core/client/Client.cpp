#include "Client.hpp"

lso::Client::State::State(Client & client) : context(client) {
    int maxHeight;
    int maxWidth;

    getmaxyx(stdscr, maxHeight, maxWidth);

    outputWindow = std::make_unique<OutputWindow>(maxHeight - 3, maxWidth, 0, 0);
    inputWindow = std::make_unique<InputWindow>(3, maxWidth, maxHeight - 3, 0);
}

void lso::Client::State::handleServerEvents(const Message & message) {
    switch (message.getType()) {
        case EVT_JOIN_REQUEST:
            break;
        case EVT_GAME_UPDATE:
            break;
        case EVT_GAME_CREATED:
            break;
        case EVT_GAME_ENDED:
            break;
        case EVT_UPDATE_BOARD:
            break;
        case EVT_NEXT_TURN:
            break;
        case EVT_GAME_WON:
            break;
        case EVT_GAME_LOST:
            break;
        case EVT_GAME_DRAW:
            break;
        default:
            context.receiveQueue.Enqueue(message);
    }
}

// --------------------------------------------------------------------------------

void lso::Client::LoginState::print() const {
    outputWindow -> clear();

    std::ostringstream stream;

    stream
        << "===========================================" << std::endl
        << "      (: BENVENUTO A CONNECT FOUR :)       " << std::endl
        << "===========================================" << std::endl;

    outputWindow -> print(stream.str());
}

void lso::Client::LoginState::handleUserInput() {
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

void lso::Client::MenuState::print() const {
    outputWindow -> clear();

    std::ostringstream stream;

    stream
        << "MENU PRINCIPALE" << std::endl
        << "1. " << MenuOption::CREATE_MATCH << std::endl
        << "2. " << MenuOption::LIST_GAMES << std::endl
        << "3. " << MenuOption::EXIT << std::endl;
    
    outputWindow -> print(stream.str());
}

void lso::Client::MenuState::handleUserInput() {
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
        case MenuOption::CREATE_MATCH: {
            context.send(Message(REQ_CREATE_GAME));
            inputWindow -> addTitle("In attesa di risposta dal server...");
            
            Message response = context.receive();
            Game game = response.getPayload<Game>(std::make_unique<GameStrategy>());
            
            context.transitionTo(std::make_unique<LobbyState>(context, game));
        }
        break;

        case MenuOption::LIST_GAMES: {
            context.send(Message(REQ_GAMES_LIST));
            inputWindow -> addTitle("In attesa di risposta dal server...");

            Message response = context.receive();

            std::vector<Game> gameList = response.getPayload<std::vector<Game>>(std::make_unique<GameListStrategy>());

            context.transitionTo(std::make_unique<GameListState>(context, gameList));
        }
        break;
        
        case MenuOption::EXIT: {
            inputWindow -> addTitle("Disconnessione in corso...");
            context.send(Message(REQ_DISCONNECT));
            
            context.isRunning = false;
        }
        break;
    }

}

// --------------------------------------------------------------------------------

void lso::Client::LobbyState::print() const {
    outputWindow -> clear();

    std::ostringstream stream;

    stream
        << "============ Dettagli Partita ============" << std::endl
        << "ID Partita: " <<  lobby.getID() << std::endl
        << "Proprietario: " <<  lobby.getOwner() << std::endl
        << "Avversario: " <<  lobby.getOpponent() << std::endl
        << std::endl
        << joinRequest << std::endl
        << std::endl
        << "Digita (y / n) per rispondere a una richiesta di partecipazione" << std::endl
        << "mentre 'esci' per tornare al Menu Principale";
    
    outputWindow -> print(stream.str());
}

void lso::Client::LobbyState::handleUserInput() {
    const std::string input = inputWindow -> getInput();

    if (input.empty()) {
        inputWindow -> addTitle("Scelta vuota non supportata");
        return;
    }
    
    if (input == "y" && !joinRequest.empty()) {
        context.send(Message(REQ_JOIN_DECISION, true));

        context.transitionTo(std::make_unique<InGameState>(context, true));
        return;
    } 
    
    if (input == "n" && !joinRequest.empty()) {
        context.send(Message(REQ_JOIN_DECISION, false));

        joinRequest.clear();
        print();
        return;
    } 
    
    if (input == "esci") {
        context.send(Message(REQ_LEAVE_GAME));

        if (!joinRequest.empty())
            context.send(Message(REQ_JOIN_DECISION, false));

        context.transitionTo(std::make_unique<MenuState>(context));
        return;
    }

    inputWindow -> addTitle("Scelta non supportata");
}

void lso::Client::LobbyState::handleServerEvents(const Message & message) {
    switch (message.getType()) {
        case EVT_JOIN_REQUEST: {
            std::string opponent = message.getPayload<std::string>(std::make_unique<StringStrategy>());

            joinRequest = "Hai ricevuto una richiesta di partecipazione da " + opponent;
            print();
        }    
        break;

        default:
            State::handleServerEvents(message);
    }
}

// --------------------------------------------------------------------------------

lso::Client::InGameState::InGameState(Client & context, const bool owner) : State(context), board(), owner(owner) {
    if (owner)
        turnState = std::make_unique<TurnState>(context, * this);
    else
        turnState = std::make_unique<WaitingState>(context, * this);
}

void lso::Client::InGameState::changeTurnTo(std::unique_ptr<State> state) {
    std::lock_guard<std::recursive_mutex> lock(context.stateTransition);
    
    turnState = std::move(state);

    nextTurn.store(false);
    nextTurn.notify_all();
}

void lso::Client::InGameState::handleUserInput() {
    turnState -> handleUserInput();

    nextTurn.wait(true);
}

void lso::Client::InGameState::TurnState::print() const {
    outputWindow -> clear();

    std::ostringstream stream;

    stream
        << "================= Partita =================" << std::endl
        << std::endl
        << gameContext.board.toString() << std::endl
        << std::endl
        << "Inserisci la tua colonna" << std::endl;
    
    outputWindow -> print(stream.str());
}

void lso::Client::InGameState::TurnState::handleUserInput() {
    const std::string input = inputWindow -> getInput();

    if (input.empty()) {
        inputWindow -> addTitle("Scelta vuota non supportata");
        return;
    }

    if (! std::all_of(input.begin(), input.end(), ::isdigit)) {
        inputWindow -> addTitle("Scelta non numerica non supportata");
        return;
    }


    const unsigned int option = (unsigned int) std::stoi(input);

    context.send(Message(REQ_MOVE, option));
    inputWindow -> addTitle("In attesa di validazione della mossa...");
    
    Message response = context.receive();
        
    bool isMoveValid = response.getPayload<unsigned int>(std::make_unique<UnsignedIntStrategy>());
    

    if (!isMoveValid) {
        inputWindow -> addTitle("Mossa non valida!");
        return;
    }

    gameContext.nextTurn.store(true);
}

void lso::Client::InGameState::TurnState::handleServerEvents(const Message & message) {

    switch (message.getType()) {
        case EVT_UPDATE_BOARD: {
            Board board = message.getPayload<Board>(std::make_unique<BoardStrategy>());

            gameContext.board.update(board);
        }
        break;

        case EVT_NEXT_TURN: {
            gameContext.changeTurnTo(std::make_unique<WaitingState>(context, gameContext));
        }
        break;

        case EVT_GAME_WON: {
            gameContext.changeTurnTo(std::make_unique<RematchState>(context, EVT_GAME_WON, gameContext));
        }
        break;

        case EVT_GAME_LOST: {
            gameContext.changeTurnTo(std::make_unique<RematchState>(context, EVT_GAME_LOST, gameContext));
        }
        break;

        case EVT_GAME_DRAW: {
            gameContext.changeTurnTo(std::make_unique<RematchState>(context, EVT_GAME_DRAW, gameContext));
        }
        break;

        default:
            State::handleServerEvents(message);
    }

}

void lso::Client::InGameState::WaitingState::print() const {
    outputWindow -> clear();

    std::ostringstream stream;

    stream
        << "================= Partita =================" << std::endl
        << std::endl
        << gameContext.board.toString() << std::endl
        << std::endl
        << "In attesa dell'avversario" << std::endl;
    
    outputWindow -> print(stream.str());
}

void lso::Client::InGameState::WaitingState::handleUserInput() {
    gameContext.nextTurn.store(true);
}

void lso::Client::InGameState::WaitingState::handleServerEvents(const Message & message) {
    switch (message.getType()) {
        case EVT_UPDATE_BOARD: {
            Board board = message.getPayload<Board>(std::make_unique<BoardStrategy>());

            gameContext.board.update(board);
        }
        break;

        case EVT_NEXT_TURN: {
            gameContext.changeTurnTo(std::make_unique<TurnState>(context, gameContext));
        }
        break;

        case EVT_GAME_WON: {
            gameContext.changeTurnTo(std::make_unique<RematchState>(context, EVT_GAME_WON, gameContext));
        }
        break;

        case EVT_GAME_LOST: {
            gameContext.changeTurnTo(std::make_unique<RematchState>(context, EVT_GAME_LOST, gameContext));
        }
        break;

        case EVT_GAME_DRAW: {
            gameContext.changeTurnTo(std::make_unique<RematchState>(context, EVT_GAME_DRAW, gameContext));
        }
        break;

        default:
            State::handleServerEvents(message);
    }
}

// --------------------------------------------------------------------------------

lso::Client::InGameState::RematchState::RematchState(Client & context, const MessageType esito, InGameState & gameContext) : State(context), gameContext(gameContext) {
    switch (esito) {
        case EVT_GAME_WON: {
            notification = "Complimenti, hai vinto!";
        }
        break;

        case EVT_GAME_LOST: {
            notification = "Ops.. Hai Perso..";
        }
        break;
    
        case EVT_GAME_DRAW: {
            notification = "Che bravi, Pareggio!";
        } break;
        

        default:
        break;
    }
}

void lso::Client::InGameState::RematchState::print() const {
    outputWindow -> clear();

    std::ostringstream stream;

    stream
        << "================= Partita =================" << std::endl
        << std::endl
        << gameContext.board.toString() << std::endl
        << std::endl
        << notification << std::endl
        << "Digita (y / n) per scegliere di effettuare un rematch" << std::endl;
    
    outputWindow -> print(stream.str());
}

void lso::Client::InGameState::RematchState::handleUserInput() {
    const std::string input = inputWindow -> getInput();

    if (input.empty()) {
        inputWindow -> addTitle("Scelta vuota non supportata");
        return;
    }

    if (input == "y") {
        context.send(Message(REQ_REMATCH, true));
        handleRematchResponse();

        return;
    }

    if (input == "n") {
        context.send(Message(REQ_REMATCH, false));
        handleRematchResponse();

        return;
    }

    inputWindow -> addTitle("Scelta non supportata");
}

void lso::Client::InGameState::RematchState::handleServerEvents(const Message & message) {
    switch (message.getType()) {
        case EVT_UPDATE_BOARD: {
            Board board = message.getPayload<Board>(std::make_unique<BoardStrategy>());
            gameContext.board.update(board);
        }
        break;

        default:
            State::handleServerEvents(message);
    }
}

void lso::Client::InGameState::RematchState::handleRematchResponse() {
    inputWindow -> addTitle("In attesa dell'avversario per fare rematch...");

    Message response = context.receive();
    bool rematchAccepted = response.getPayload<unsigned int>(std::make_unique<UnsignedIntStrategy>());

    if (rematchAccepted && gameContext.owner) {
        gameContext.changeTurnTo(std::make_unique<TurnState>(context, gameContext));

        return;
    }

    if (rematchAccepted && !gameContext.owner) {
        gameContext.changeTurnTo(std::make_unique<WaitingState>(context, gameContext));
    }

    if (!rematchAccepted) {
        // ?
        context.transitionTo(std::make_unique<MenuState>(context));

        return;
    }
}

// --------------------------------------------------------------------------------

lso::Client::GameListState::GameListState(Client & context, std::vector<Game> & gameList) : State(context) {
    for (Game game : gameList)
        lobbyList.push_back(Lobby(game));
}

void lso::Client::GameListState::print() const {
    outputWindow -> clear();

    std::ostringstream stream;

    stream
        << "============== Lista Partite ==============" << std::endl
        << std::endl
        << getNotification() << std::endl
        << std::endl
        << getLobbyList()
        << std::endl
        << "Digita il numero della Partita per inviare una richiesta di partecipazione" << std::endl
        << "mentre 0 per tornare al Menu Principale";
    
    outputWindow -> print(stream.str());
}

void lso::Client::GameListState::handleUserInput() {
    const std::string input = inputWindow -> getInput();

    if (input.empty()) {
        inputWindow -> addTitle("Scelta vuota non supportata");
        return;
    }

    if (! std::all_of(input.begin(), input.end(), ::isdigit)) {
        inputWindow -> addTitle("Scelta non numerica non supportata");
        return;
    }

    const unsigned int option = (unsigned int) std::stoi(input);

    if (option == 0) {
        context.transitionTo(std::make_unique<MenuState>(context));
        return;
    }

    context.send(Message(REQ_JOIN_GAME, option));
    inputWindow -> addTitle("In attesa di risposta...");

    Message response = context.receive();
    bool accepted = response.getPayload<unsigned int>(std::make_unique<UnsignedIntStrategy>());

    if (accepted) {
        Lobby lobby = findLobby(option);

        context.transitionTo(std::make_unique<InGameState>(context, false));
    } else {
        inputWindow -> addTitle("Richiesta di partecipazione rifiutata");
    }
}

void lso::Client::GameListState::handleServerEvents(const Message & message) {
    switch (message.getType()) {
        case EVT_GAME_UPDATE: {
            Game game = message.getPayload<Game>(std::make_unique<GameStrategy>());
            
            updateLobby(Lobby(game));
            notification = "La Partita con ID " + std::to_string(game.id) + " è stata aggiornata!";

            print();
        }
        break;

        case EVT_GAME_CREATED: {
            Game game = message.getPayload<Game>(std::make_unique<GameStrategy>());
            
            lobbyList.push_back(Lobby(game));
            notification = "La Partita con ID " + std::to_string(game.id) + " è stata appena creata!";

            print();
        }
        break;

        case EVT_GAME_ENDED: {
            unsigned int id = message.getPayload<unsigned int>(std::make_unique<UnsignedIntStrategy>());
            
            removeLobby(id);
            notification = "La Partita con ID " + std::to_string(id) + " è terminata!";

            print();
        }
        break;

        default:
            State::handleServerEvents(message);
    }
}

std::string lso::Client::GameListState::getLobbyList() const {
    std::ostringstream stream;

    if (lobbyList.empty())
        stream << "Nessuna partita presente" << std::endl;
    else
        for (const Lobby & lobby : lobbyList)
            stream
                << lobby.getID() << ") "
                << lobby.getOwner()
                << " VS "
                << lobby.getOpponent()
                << std::endl; 

    return stream.str();
}

lso::Lobby lso::Client::GameListState::findLobby(const unsigned int target) {
    std::vector<Lobby>::iterator lobby = std::find_if(
        lobbyList.begin(),
        lobbyList.end(),
        [target] (const Lobby & lobby) {
            return lobby.getID() == target;
        }
    );

    if (lobby == lobbyList.end())
        throw std::runtime_error("Expected to find lobby..");

    return * lobby;
}

void lso::Client::GameListState::updateLobby(const Lobby & target) {
    std::vector<Lobby>::iterator lobby = std::find_if(
        lobbyList.begin(),
        lobbyList.end(),
        [& target] (const Lobby & lobby) {
            return lobby == target;
        }
    );

    if (lobby == lobbyList.end())
        return;

    * lobby = target;
}

void lso::Client::GameListState::removeLobby(const unsigned int target) {
    std::vector<Lobby>::iterator lobby = std::find_if(
        lobbyList.begin(),
        lobbyList.end(),
        [target] (const Lobby & lobby) {
            return lobby.getID() == target;
        }
    );

    if (lobby == lobbyList.end())
        return;

    lobbyList.erase(lobby);
}

// --------------------------------------------------------------------------------

void lso::Client::handleEventLoop() {
    Message event;

    while (eventQueue.Dequeue(event)) {
        std::lock_guard<std::recursive_mutex> lock(stateTransition);

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
    std::lock_guard<std::recursive_mutex> lock(stateTransition);

    state = std::move(nextState);
}

void lso::Client::startThreads() {
    senderThread = std::thread(& Client::sendLoop, this);
    eventHandlerThread = std::thread(& Client::handleEventLoop, this);
    receiverThread = std::thread(& Client::receiveLoop, this);
}

lso::Message lso::Client::receive() {
    Message message;

    receiveQueue.Dequeue(message);
    

    return message;
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
