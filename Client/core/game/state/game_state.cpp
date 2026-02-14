#include "game_state.hpp"

namespace lso {

    void MyTurnState::makeMove(Board & board, const unsigned int column) const {
        board.addMove(column, game.myColor);

        game.changeStateTo(std::make_unique<EnemyTurnState>(game));
    }

    void EnemyTurnState::makeMove(Board & board, const unsigned int columns) const {
        board.addMove(columns, game.enemyColor);

        game.changeStateTo(std::make_unique<MyTurnState>(game));
    }

}
