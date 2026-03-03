#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <memory>
#include <vector>

#include "../shared/protocol.h"

namespace lso {

    class Message {
        private:

            MessageType type;
            std::vector<uint32_t> payload;
            
        protected:
            
            // ...

        public:
            
            inline const MessageType & getType() const noexcept { return type; };
            inline uint32_t getLength() const noexcept { return payload.size(); };
            inline const std::vector<uint32_t> & getPayload() const noexcept { return payload; };

        public:
        
            Message(const MessageType type) : type(type), payload(std::vector<uint32_t>()) {};
            Message(const MessageType type, const std::vector<uint32_t> & payload) : type(type), payload(std::vector<uint32_t>(payload)) {};
            
            Message(const Message & other) : type(other.type), payload(other.payload) {};
            Message(Message && other) noexcept : type(std::move(other.type)), payload(std::move(other.payload)) {};

            ~Message() = default;

            Message &operator = (const Message &) = delete;
            Message &operator = (Message &&) noexcept = delete;

            bool operator == (const Message & other) const noexcept { return type == other.type && payload == other.payload; };
            bool operator != (const Message & other) const noexcept { return ! (*this == other); };

    };

}

#endif
