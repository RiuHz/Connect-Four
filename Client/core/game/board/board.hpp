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

            static inline std::string emptySymbol = "·";
            static inline std::string playerSymbol = "O";

            std::vector< std::vector<std::string> > grid;

            void printRow(const unsigned int row) const noexcept;

            void printSeparator() const noexcept;

            void printColumnNumbers() const noexcept;

            unsigned int findDeepestEmptyRow(const unsigned int column) const;
            
        protected:
            
            //...
            
        public:
            
            Board() : grid(rows, std::vector<std::string>(columns, emptySymbol)) {}
            
            static inline constexpr unsigned int columns = 6;
            static inline constexpr unsigned int rows = 7;

            void printBoard() const noexcept;
            
            void addMove(const unsigned int column, const TextColor color) noexcept;

        public:

            Board(const Board &) = delete;
            Board(Board &&) noexcept = delete;

            ~Board() = default;

            Board &operator = (const Board &) = delete;
            Board &operator = (Board &&) noexcept = default;

            bool operator == (const Board &) const noexcept = delete;
            bool operator != (const Board &) const noexcept = delete;
            
    };

}

#endif
