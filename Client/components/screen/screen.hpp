#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>

namespace lso {

    class Screen {
        private:

            Screen();
        
        protected:
        
            //...
        
        public:
        
            static inline constexpr void open() { std::cout << "\033[?1049h\033[?25l" << std::flush; };

            static inline constexpr void close() { std::cout << "\033[?25h\033[?1049l" << std::flush; };

            static inline constexpr void clear() { std::cout << "\033[H\033[2J" << std::flush; };

        public:

            Screen &operator = (const Screen &) = delete;

            Screen &operator = (Screen &&) noexcept = delete;

            bool operator == (const Screen &) const noexcept = delete;
            bool operator != (const Screen &) const noexcept = delete;

    };

}

#endif
