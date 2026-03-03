#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <climits>
#include <string_view>

#include "../../enum/TextStyles.hpp"

#include "../../enum/TextStyles.hpp"
#include "../../enum/TextColors.hpp"

#include "../../../network/shared/protocol.h"

namespace lso {

    class Board {

        private:

            // * Potrebbe dover sparire
            static inline unsigned int invalidGridValue = UINT_MAX;

            static inline unsigned int columns = BOARD_COLUMNS;
            static inline unsigned int rows = BOARD_ROWS;

            std::vector< std::vector<std::string> > grid;

            static const inline std::string emptySymbol = "·";
            static const inline std::string playerSymbol = "O";

            void printRow(const unsigned int row) const noexcept;

            void printSeparator() const noexcept;

            void printColumnNumbers() const noexcept;
            
        protected:
            
            //...
            
        public:
            
            Board() : grid(rows, std::vector<std::string>(columns, emptySymbol)) {}
            
            void print() const noexcept; 

        public:

            Board(const Board &) = delete;
            Board(Board &&) noexcept = default;

            ~Board() = default;

            Board &operator = (const Board &) = delete;
            Board &operator = (Board &&) noexcept = default;

            bool operator == (const Board &) const noexcept = delete;
            bool operator != (const Board &) const noexcept = delete;
    };

}

#endif
