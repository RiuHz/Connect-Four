#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <climits>

#include "../../enum/TextStyles.hpp"
#include "../../enum/TextColors.hpp"

namespace lso {

    class Board {

        public:

            Board() {};

            void printBoard();

            void addRedMove(const unsigned int column) { addMove(column, TextColor::RED); };
            
            void addYellowMove(const unsigned int column) { addMove(column, TextColor::YELLOW); };
            
        protected:

            //...

        private:

            const unsigned int invalidGridValue = UINT_MAX;

            const unsigned int columns = 8;
            const unsigned int rows = 8;

            const std::string emptySymbol = "·";
            const std::string playerSymbol = "O";

            std::vector< std::vector<std::string> > grid {
                rows,
                std::vector<std::string>(columns, emptySymbol)
            };

            void printRow(const unsigned int row);

            void printSeparator();

            void printColumnNumbers();

            void addMove(const unsigned int column, const TextColor color);

            unsigned int findDeepestEmptyRow(const unsigned int column);

    };

}


#endif
