#include "board.hpp"

namespace lso {

    void Board::printBoard() {
        for (unsigned int row = 0; row < rows; row++)
            Board::printRow(row);

            Board::printSeparator();
            Board::printColumnNumbers();
    }

    void Board::printRow(const unsigned int row) {
        std::cout << TextColor::BLUE << '|' << TextColor::WHITE;

        for (unsigned int column = 0; column < columns; column++)
            std::cout << " " << grid[row][column] << " ";

        std::cout << TextColor::BLUE << '|' << TextColor::WHITE << std::endl;
    }

    void Board::printSeparator() {
        std::cout << TextColor::BLUE << '+';

        for (unsigned int column = 0; column < columns; column++)
            std::cout << "---";

        std::cout << '+' << TextColor::WHITE << std::endl;
    }

    void Board::printColumnNumbers() {
        std::cout << TextColor::BLUE << '|' << TextColor::WHITE;

        for (unsigned int column = 0; column < columns; column++) {
            std::cout << ' ' << column + 1 << ' ';
        }

        std::cout << TextColor::BLUE << '|' << TextColor::WHITE << std::endl;
    }

    void Board::addMove(const unsigned int column, const TextColor color) {        
        unsigned int row = findDeepestEmptyRow(column);

        grid[row][column] = color + playerSymbol + TextStyle::RESET;
    }

    unsigned int Board::findDeepestEmptyRow(const unsigned int column) {
        for (unsigned int row = rows - 1; row != invalidGridValue; row--)
            if (grid[row][column] == emptySymbol)
                return row;

        throw std::logic_error("Expected to find an empty row...");
    }

}
