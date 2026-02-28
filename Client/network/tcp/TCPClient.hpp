#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <cstring> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdint> 

    class TCPClient {
        private:

            int clientSocket;

            bool connected;
            
        protected:
            
            // ...

        public:

            TCPClient();
            ~TCPClient();

            // Tenta la connessione. Restituisce true se ha successo.
            bool connectToServer(const std::string& serverIp, uint16_t serverPort);
            
            // Chiude il socket
            void disconnect();
            
            // Verifica lo stato
            bool isConnected() const;

            // Invia una stringa al server
            bool sendData(const std::string& data);
            
            // Riceve una stringa dal server (ATTENZIONE: bloccante! da risolvere con thread e vedere come fare)
            std::string receiveData();

    };

#endif
