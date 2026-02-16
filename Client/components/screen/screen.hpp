#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <thread>

namespace lso {

    class Screen {
        private:

            //...
        
        protected:
        
            //...
        
        public:
        
            static inline void open() noexcept { std::cout << "\033[?1049h\033[?25l" << std::flush; };
            
            static inline void close() noexcept { std::cout << "\033[?25h\033[?1049l" << std::flush; };
            
            static inline void clear() noexcept { std::cout << "\033[H\033[2J" << std::flush; };

            static inline void briefDisplay(const std::string text) noexcept { std::cout << text << std::flush; std::this_thread::sleep_for(std::chrono::seconds(1)); };
        
        public:
        
            Screen() = delete;
            Screen(const Screen &) = delete;
            Screen(Screen &&) noexcept = delete;

            ~Screen() = default;

            Screen &operator = (const Screen &) = delete;
            Screen &operator = (Screen &&) noexcept = delete;

            bool operator == (const Screen &) const noexcept = delete;
            bool operator != (const Screen &) const noexcept = delete;

    };

}

#endif
