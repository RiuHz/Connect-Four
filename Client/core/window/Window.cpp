#include "Window.hpp"

lso::Window::Window(const int height, const int width, const int startY, const int startX) {
    window = newwin(height, width, startY, startX);
}

// --------------------------------------------------------------------------------

void lso::OutputWindow::print(const std::string & text) {
    werase(window);

    wmove(window, 0, 0);
    wprintw(window, "%s", text.c_str());

    wrefresh(window);
}

// --------------------------------------------------------------------------------

lso::InputWindow::InputWindow(const int height, const int width, const int startY, const int startX) : Window(height, width, startY, startX) {
    noecho();
    cbreak();

    box(window, 0, 0);
    
    innerWindow = derwin(window, height - 2, width - 2, 1, 1);

    wrefresh(window);
}

void lso::InputWindow::addTitle(const std::string & text) {
    werase(window);
    
    box(window, 0, 0);
    wmove(window, 0, 1);
    wprintw(window, "%s", text.c_str());

    wrefresh(window);
}

void lso::InputWindow::print(const std::string & text) {
    werase(innerWindow);

    wmove(innerWindow, 0, 0);
    wprintw(innerWindow, "> ");
    wprintw(innerWindow, "%s", text.c_str());

    wrefresh(innerWindow);
}

std::string lso::InputWindow::getInput() {
    std::string input;
    int ch;

    do {

        ch = wgetch(innerWindow);

        if ( (ch == 127 || ch == 8) && !input.empty())
            input.pop_back();
        else if (isprint(ch))
            input.push_back((char) ch);

        print(input);

    } while (ch != '\n' && ch != '\r');

    return input;
}
