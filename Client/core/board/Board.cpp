#include "Board.hpp"

void lso::Board::print() const {
    for (unsigned int row = 0; row < rows; row++)
        Board::printRow(row);

    Board::printSeparator();
    Board::printColumnNumbers();
}

void lso::Board::printRow(const unsigned int row) const {
    std::cout << TextColor::BLUE << '|' << TextColor::WHITE;

    for (unsigned int column = 0; column < columns; column++)
        std::cout << " " << grid[row][column] << " ";

    std::cout << TextColor::BLUE << '|' << TextStyle::RESET << std::endl;
}

void lso::Board::printSeparator() const {
    std::cout << TextColor::BLUE << '+';

    for (unsigned int column = 0; column < columns; column++)
        std::cout << "---";

    std::cout << '+' << TextStyle::RESET << std::endl;
}

void lso::Board::printColumnNumbers() const {
    std::cout << TextColor::BLUE << '|' << TextColor::WHITE;

    for (unsigned int column = 0; column < columns; column++) {
        std::cout << ' ' << column + 1 << ' ';
    }

    std::cout << TextColor::BLUE << '|' << TextStyle::RESET << std::endl;
}
