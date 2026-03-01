#ifndef TEXT_COLORS_HPP
#define TEXT_COLORS_HPP

#include <iostream>
#include <unordered_map>
#include <string>

namespace lso {

    enum TextColor {
        WHITE,
        RED,
        BLUE,
        GREEN,
        YELLOW
    };

    const std::unordered_map<TextColor, const std::string> textColors = {
        {TextColor::WHITE, "\033[37m"},
        {TextColor::RED, "\033[31m"},
        {TextColor::BLUE, "\033[34m"},
        {TextColor::GREEN, "\033[32m"},
        {TextColor::YELLOW, "\033[33m"}
    };

    inline std::ostream & operator << (std::ostream & os, TextColor color) {
        return os << textColors.at(color);
    };

}

#endif
