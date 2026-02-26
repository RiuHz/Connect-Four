#ifndef TEXT_STYLE_HPP
#define TEXT_STYLE_HPP

#include <iostream>
#include <unordered_map>
#include <string>

namespace lso {

    enum TextStyle {
        RESET,
        ITALIC,
        BOLD
    };

    const std::unordered_map<TextStyle, const std::string> textStyles = {
        {TextStyle::RESET, "\033[0m"},
        {TextStyle::ITALIC, "\033[3m"},
        {TextStyle::BOLD, "\033[1m"}
    };

    inline std::ostream & operator << (TextStyle style, std::ostream & os) {
        return os << textStyles.at(style);
    };

    inline std::ostream & operator << (std::ostream & os, TextStyle style) {
        return os << textStyles.at(style);
    };

    inline std::string operator + (TextStyle style, const std::string & text) {
        return textStyles.at(style) + text;
    }

    inline std::string operator + (const std::string & text, TextStyle style) {
        return text + textStyles.at(style);
    }

}

#endif
