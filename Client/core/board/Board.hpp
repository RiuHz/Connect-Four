#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>

#include "../../enum/text/TextStyles.hpp"
#include "../../enum/text/TextColors.hpp"

#include "../../network/shared/protocol.h"

namespace lso {

    class Board {

        private:

            inline const unsigned int columns = BOARD_COLUMNS;
            inline const unsigned int rows = BOARD_ROWS;

            // ? Questa va cambiata in unsigned int o la conversione avviene all'update?
            std::vector< std::vector<std::string> > grid;

            const inline std::string emptySymbol = "·";
            const inline std::string playerSymbol = "O";

            void printRow(const unsigned int row) const;

            void printSeparator() const;

            void printColumnNumbers() const;
            
        protected:
            
            //...
            
        public:
            
            Board();
            
            void print() const; 

        public:

            Board(const Board &) = delete;
            Board(Board &&) noexcept = delete;

            ~Board() = default;

            Board &operator = (const Board &) = delete;
            Board &operator = (Board &&) noexcept = delete;

            bool operator == (const Board &) const noexcept = delete;
            bool operator != (const Board &) const noexcept = delete;
    };

}

#endif
