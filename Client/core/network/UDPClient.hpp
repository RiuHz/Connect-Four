#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include <string>
#include <unistd.h>
#include <stdexcept>    
#include <sys/socket.h> 
#include <arpa/inet.h>

namespace lso {

    class UDPClient {
        private:

            int clientSocket;

            struct sockaddr_in serverAddress;
            
            const int MAXLINE = 1024;

        protected:

            // ...

        public:

            UDPClient(std::string server_ip, __uint16_t server_port);
            
            ~UDPClient();

            void sendMessage(std::string message);

            void receiveMessage();
    };

}

#endif