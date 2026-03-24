#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "../../network/shared/protocol.h"

namespace lso {

    class GameBoard {

        private:

            const unsigned int columns = BOARD_COLUMNS;
            const unsigned int rows = BOARD_ROWS;

            const std::string emptySymbol = "·";
            const std::string playerSymbol = "O";
            const std::string opponentSymbol = "X";
            
            std::vector< std::vector<std::string> > grid;

            std::string rowToString(const unsigned int row) const;

            std::string separatorToString() const;

            std::string columnNumbersToString() const;

            inline unsigned int invert(unsigned int row) const noexcept { return rows - row - 1; };

        protected:
            
            //...
            
        public:
            
            GameBoard() : grid(rows, std::vector<std::string>(columns, emptySymbol)) {};

            void update(const Board board);
            
            std::string toString() const; 

        public:

            GameBoard(const GameBoard &) = default;
            GameBoard(GameBoard &&) noexcept = delete;

            ~GameBoard() = default;

            GameBoard &operator = (const GameBoard &) = delete;
            GameBoard &operator = (GameBoard &&) noexcept = delete;

            bool operator == (const GameBoard &) const noexcept = delete;
            bool operator != (const GameBoard &) const noexcept = delete;

    };

}

#endif
