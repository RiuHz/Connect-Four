#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>

#include "../shared/protocol.h"

namespace lso {
    
    class Message {
        private:
            
            MessageType type;
            std::vector<uint32_t> message;

        protected:

            //...

        public:

            MessageType getType() const noexcept { return static_cast<MessageType>(type); };

            std::size_t getLength() const noexcept { return message.size(); };

            const std::vector<uint32_t> & getPayload() const noexcept { return message; };

        public:

            Message(MessageType type) : Message(type, {}) {};
            Message(MessageType type, std::vector<uint32_t> message) : type(type), message(std::move(message)) {};

            Message(const Message &) = default;
            Message(Message &&) noexcept = default;

            ~Message() = default;

            Message &operator = (const Message &) = default;
            Message &operator = (Message &&) noexcept = default;

            bool operator == (const Message & other) const noexcept { return type == other.type && message == other.message; };
            bool operator != (const Message & other) const noexcept { return ! operator == (other); };
        
    };

}

#endif
