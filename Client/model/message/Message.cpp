#include "Message.hpp"

lso::Message::Message(const MessageType type, const std::string & string) : type(type) {

    for (size_t byteIndex = 0; byteIndex < string.size(); byteIndex += 4) {
        uint32_t word = 0;

        for (size_t byteOffset = 0; byteOffset < 4; byteOffset++)
            word |= ( static_cast<uint32_t>(string[byteIndex + byteOffset]) << (8 * byteOffset) );

        payload.push_back(word);
    }
}

lso::Message::Message(const MessageType type, const unsigned int number) : type(type) {
    payload.push_back(static_cast<uint32_t>(number));
}
