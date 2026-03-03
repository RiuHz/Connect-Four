#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>

#include "../../model/message/Message.hpp"

#include "../shared/protocol.h"

namespace lso {

    class TCPClient {
        private:

            int TCPSocket;

        private:
            
            void connectTCPClient();
            inline void disconnectTCPClient() { close(TCPSocket); };

            void sendData(const uint32_t data) const;
            void sendData(const std::vector<uint32_t> & payload, const size_t length) const;

            const std::vector<uint32_t> receiveData(const uint32_t length) const;

        protected:
            
            // ...

        public:
            
            void sendMessage(const Message & message) const;
            
            const Message receiveMessage() const;

        public:
        
            TCPClient() { connectTCPClient(); };
            TCPClient(const TCPClient &) = delete;
            TCPClient(TCPClient &&) noexcept = delete;

            ~TCPClient() { disconnectTCPClient(); };

            TCPClient &operator = (const TCPClient &) = delete;
            TCPClient &operator = (TCPClient &&) noexcept = delete;

            bool operator == (const TCPClient &) const noexcept = delete;
            bool operator != (const TCPClient &) const noexcept = delete;

    };

}

#endif
