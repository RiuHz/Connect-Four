#include "GameBoard.hpp"

std::string lso::GameBoard::rowToString(const unsigned int row) const {
    std::ostringstream stream;
    
    stream << '|';

    for (unsigned int column = 0; column < columns; column++)
        stream << " " << grid[row][column] << " ";

    stream << '|' << std::endl;

    return stream.str();
}

std::string lso::GameBoard::separatorToString() const {
    std::ostringstream stream;
    
    stream << '+';

    for (unsigned int column = 0; column < columns; column++)
        stream << "---";

    stream << '+' << std::endl;

    return stream.str();
}

std::string lso::GameBoard::columnNumbersToString() const {
    std::ostringstream stream;

    stream << '|';

    for (unsigned int column = 0; column < columns; column++) {
        stream << ' ' << column + 1 << ' ';
    }

    return stream.str();
}

std::string lso::GameBoard::toString() const {
    std::ostringstream stream;

    for (unsigned int row = 0; row < rows; row++)
        stream << rowToString(row);

    stream
        << separatorToString()
        << columnNumbersToString();

    return stream.str();
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
