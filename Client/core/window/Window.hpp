#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <thread>
#include <string>

#include <ncurses.h>

namespace lso {

    class Window {
        private:

            // ...
        
        protected:
        
            WINDOW * window;
        
        public:

            virtual void print(const std::string & text) = 0;
        
        public:
        
            Window(const int height, const int width, const int startY, const int startX);

            Window(const Window &) = delete;
            Window(Window &&) noexcept = delete;

            virtual ~Window() { delwin(window); };

            Window &operator = (const Window &) = delete;
            Window &operator = (Window && other) noexcept = delete;

            bool operator == (const Window &) const noexcept = delete;
            bool operator != (const Window &) const noexcept = delete;

    };

    class OutputWindow : public Window {
        private:

            // ...
        
        protected:
        
            // ...
        
        public:

            using Window::Window;

            void print(const std::string & text) override;

            void clear() { wclear(window); };
        
    };

    class InputWindow : public Window {
        private:

            // ...

        protected:

            WINDOW * innerWindow;

            void print(const std::string & text) override;

        public:

            void addTitle(const std::string & text);

            std::string getInput();
        
        public:

            InputWindow(const int height, const int width, const int startY, const int startX);

    };

}

#endif
