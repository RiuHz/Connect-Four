#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <memory>
#include <vector>

#include "../../network/shared/protocol.h"
#include "../../network/strategy/Strategy.hpp"

namespace lso {

    class Message {
        private:

            MessageType type;
            std::vector<uint32_t> payload;

        protected:
            
            // ...
            
        public:
            
            inline const MessageType & getType() const noexcept { return type; };
            inline size_t getLength() const noexcept { return payload.size() * sizeof(uint32_t); };
            inline const std::vector<uint32_t> & getPayload() const noexcept { return payload; }
            
            template <typename Data>
            inline const Data getPayload(std::unique_ptr<Strategy<Data>> strategy) const noexcept { return strategy -> convertToHost(payload); };
            
        public:

            Message() {};
            
            Message(const MessageType type) : type(type), payload(std::vector<uint32_t>()) {};
            Message(const MessageType type, const std::vector<uint32_t> & payload) : type(type), payload(payload) {};
            
            Message(const MessageType type, const std::string & string);
            Message(const MessageType type, const unsigned int number);
            
            Message(const Message & other) : type(other.type), payload(other.payload) {};
            Message(Message && other) noexcept : type(std::move(other.type)), payload(std::move(other.payload)) {};

            ~Message() = default;

            Message & operator = (const Message &) = default;
            Message & operator = (Message &&) noexcept = default;

            bool operator == (const Message & other) const noexcept { return type == other.type && payload == other.payload; };
            bool operator != (const Message & other) const noexcept { return ! (*this == other); };

    };

}

#endif
