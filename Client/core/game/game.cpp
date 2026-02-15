#include "game.hpp"

namespace lso {

    void Game::PlayerTurn::makeMove(Board & board, const unsigned int column) const {
        board.addMove(column, game.playerColor);

        game.changeTurnTo(new EnemyTurn(game));
    }

    unsigned int Game::PlayerTurn::takeInput() const {
        unsigned int column = 0;
        
        std::cout << std::endl
            << "Inserisci la tua mossa" << std::endl
            << "> ";

        std::cin >> column;

        return column - 1;
    }

    void Game::EnemyTurn::makeMove(Board & board, const unsigned int column) const {
        board.addMove(column, game.enemyColor);

        game.changeTurnTo(new PlayerTurn(game));
    }

    unsigned int Game::EnemyTurn::takeInput() const {
        unsigned int column = 0;
        
        std::cout << std::endl
            << "Inserisci la tua mossa" << std::endl
            << "> ";

        std::cin >> column;

        return column - 1;
    }

    Game::Game(const bool owner) :
        board(),
        playerColor(owner ? TextColor::RED : TextColor::YELLOW),
        enemyColor(owner ? TextColor::YELLOW : TextColor::RED),
        turn(owner ? static_cast<Turn *> (new PlayerTurn(*this)) : static_cast<Turn *> (new EnemyTurn(*this)))
    {}

    bool Game::validMove(const unsigned int column) {
        try {
            makeMove(column);
        } catch (std::out_of_range & exception) {
            Screen::briefDisplay("Mossa non valida");

            return false;
        }

        return true;
    }

    void Game::playTurn() {
        unsigned int input = 0;

        do {

            Screen::clear();
            print();
            input = takeInput();

        } while ( !validMove(input) );

    }

    void Game::print() const {
        std::cout
            << "Lobby \'n\'" << std::endl
            << playerName << " " << playerColor << "O" << TextStyle::RESET
            << " VS "
            << enemyName << " " << enemyColor << "O" << TextStyle::RESET
            << std::endl
            << std::endl;

        board.print();        
    }

    void Game::changeTurnTo(Turn * turn) {
        if (this -> turn != nullptr)
            delete this -> turn;

        this -> turn = std::move(turn);
    }

    void Game::start() {
        for (int i = 0; i < 10; i++) { // Qui va sistemata la logica, deve essere il server a dirmi cosa fare..
            playTurn();
        }
    }

}
