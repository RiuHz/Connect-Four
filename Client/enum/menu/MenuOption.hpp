#ifndef MENU_OPTION_HPP
#define MENU_OPTION_HPP

#include <iostream>
#include <unordered_map>
#include <string>

namespace lso {

    enum class MenuOption {
        CREATE_MATCH = 1,
        LIST_GAMES,
        EXIT
    };

    const std::unordered_map<MenuOption, const std::string> menuOptions = {
        {MenuOption::CREATE_MATCH, "Crea Partita"},
        {MenuOption::LIST_GAMES, "Lista Partite"},
        {MenuOption::EXIT, "Esci"}
    };

    inline std::ostream & operator << (std::ostream & os, MenuOption opzione) {
        return os << menuOptions.at(opzione);
    };

}

#endif
