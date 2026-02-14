#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <climits>
#include <string_view>

#include "../../enum/TextStyles.hpp"
#include "../../enum/TextColors.hpp"

namespace lso {

    class Board {

        private:

            static inline constexpr unsigned int invalidGridValue = UINT_MAX;

            static inline constexpr unsigned int columns = 6;
            static inline constexpr unsigned int rows = 7;

            static inline std::string emptySymbol = "·";
            static inline std::string playerSymbol = "O";

            std::vector< std::vector<std::string> > grid;

            void printRow(const unsigned int row);

            void printSeparator();

            void printColumnNumbers();

            void addMove(const unsigned int column, const TextColor color);

            unsigned int findDeepestEmptyRow(const unsigned int column);

        protected:

            //...

        public:

            Board() : grid(rows, std::vector<std::string>(columns, emptySymbol)) {}

            void printBoard();

            void inline addRedMove(const unsigned int column) { addMove(column, TextColor::RED); };
            
            void inline addYellowMove(const unsigned int column) { addMove(column, TextColor::YELLOW); };

        public:

            Board &operator = (const Board &) = delete;

            Board &operator = (Board &&) noexcept = delete;

            bool operator == (const Board &) const noexcept = delete;
            bool operator != (const Board &) const noexcept = delete;
            
    };

}

#endif
