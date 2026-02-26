#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <string>
#include <unistd.h>
#include <stdexcept>    
#include <sys/socket.h> 
#include <arpa/inet.h>

#include "../message/Message.hpp"
#include "../shared/protocol.h"

namespace lso {

    class TCPClient {
        private:

            int clientSocket;

            struct sockaddr_in serverAddress;

            void sendMessageHeader(const Message & message) const;

            void sendMessagePayload(const Message & message) const;

            MessageHeader receiveMessageHeader() const;

            std::vector<uint32_t> receiveMessagePayload(const unsigned int length) const;
            
        protected:
            
            // ...
            
        public:
            
            void sendMessage(const Message message) const;

            Message receiveMessage() const;

        public:

            TCPClient(const std::string server_ip, const unsigned int server_port);
            
            TCPClient(const TCPClient &) = delete;
            TCPClient(TCPClient &&) noexcept = default;

            ~TCPClient() { close(clientSocket); }

            TCPClient &operator = (const TCPClient &) = delete;
            TCPClient &operator = (TCPClient &&) noexcept = default;

            bool operator == (const TCPClient & other) const noexcept;
            bool operator != (const TCPClient & other) const noexcept { return ! operator == (other); };

    };

}

#endif
