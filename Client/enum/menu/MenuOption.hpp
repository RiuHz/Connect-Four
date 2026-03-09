#ifndef MENU_OPTION_HPP
#define MENU_OPTION_HPP

#include <iostream>
#include <map>
#include <string>

namespace lso {

    enum class MenuOption {
        CREATE_MATCH = 1,
        LIST_GAMES,
        EXIT
    };

    const std::map<MenuOption, std::string> toString = {
        {MenuOption::CREATE_MATCH, "Crea Partita"},
        {MenuOption::LIST_GAMES, "Lista Partite"},
        {MenuOption::EXIT, "Esci"}
    };

}

#endif
