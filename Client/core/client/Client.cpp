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
