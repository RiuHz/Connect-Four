#include "GameBoard.hpp"

void lso::GameBoard::printRow(const unsigned int row) const {
    std::cout << TextColor::BLUE << '|' << TextColor::WHITE;

    for (unsigned int column = 0; column < columns; column++)
        std::cout << " " << grid[row][column] << " ";

    std::cout << TextColor::BLUE << '|' << TextStyle::RESET << std::endl;
}

void lso::GameBoard::printSeparator() const {
    std::cout << TextColor::BLUE << '+';

    for (unsigned int column = 0; column < columns; column++)
        std::cout << "---";

    std::cout << '+' << TextStyle::RESET << std::endl;
}

void lso::GameBoard::printColumnNumbers() const {
    std::cout << TextColor::BLUE << '|' << TextColor::WHITE;

    for (unsigned int column = 0; column < columns; column++) {
        std::cout << ' ' << column + 1 << ' ';
    }

    std::cout << TextColor::BLUE << '|' << TextStyle::RESET << std::endl;
}

void lso::GameBoard::print() const {
    for (unsigned int row = 0; row < rows; row++)
        GameBoard::printRow(row);

    GameBoard::printSeparator();
    GameBoard::printColumnNumbers();
}

void lso::GameBoard::update(const Board board) {
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int column = 0; column < columns; column++) {

            switch (board.grid[row][column]) {
                case CELLA_PROPRIETARIO:
                    grid[invert(row)][column] = playerSymbol;
                break;

                case CELLA_AVVERSARIO:
                    grid[invert(row)][column] = opponentSymbol;
                break;
            }
        }
    }
}
