#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <iostream>
#include <vector>
#include <string>

#include "../../enum/text/TextStyles.hpp"
#include "../../enum/text/TextColors.hpp"

#include "../../network/shared/protocol.h"

namespace lso {

    class GameBoard {

        private:

            const unsigned int columns = BOARD_COLUMNS;
            const unsigned int rows = BOARD_ROWS;

            std::vector< std::vector<std::string> > grid;

            const std::string emptySymbol = "·";
            const std::string playerSymbol = colorToString.at(TextColor::YELLOW) + "O" + styleToString.at(TextStyle::RESET);
            const std::string opponentSymbol = colorToString.at(TextColor::RED) + "O" + styleToString.at(TextStyle::RESET);

            void printRow(const unsigned int row) const;

            void printSeparator() const;

            void printColumnNumbers() const;

            inline unsigned int invert(unsigned int row) const noexcept { return rows - row - 1; };

        protected:
            
            //...
            
        public:
            
            GameBoard() : grid(rows, std::vector<std::string>(columns, emptySymbol)) {};

            void update(const Board board);
            
            void print() const; 

        public:

            GameBoard(const Board &) = delete;
            GameBoard(Board &&) noexcept = delete;

            ~GameBoard() = default;

            GameBoard &operator = (const GameBoard &) = delete;
            GameBoard &operator = (GameBoard &&) noexcept = delete;

            bool operator == (const GameBoard &) const noexcept = delete;
            bool operator != (const GameBoard &) const noexcept = delete;
    };

}

#endif
