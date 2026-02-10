#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <string>
#include <netinet/in.h> // Necessario per struct sockaddr_in

class UDPClient {
private:
    int sockfd;
    struct sockaddr_in servaddr;
    const int MAXLINE = 1024; // solo per provare da togliere / cambiare

public:
    // Costruttore
    UDPClient(std::string server_ip, __uint16_t server_port);
    
    // Distruttore
    ~UDPClient();

    // Metodi
    void sendMessage(std::string message);
    std::string receiveMessage();
};

#endif