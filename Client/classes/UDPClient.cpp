#include "headers/UDPClient.hpp"
#include <iostream>
#include <cstring>      // memset
#include <sys/socket.h> 
#include <arpa/inet.h>  // inet_addr
#include <unistd.h>     // close
#include <stdexcept>    
#define MAXLINE 1000

// Implementazione Costruttore
UDPClient::UDPClient(std::string server_ip, __uint16_t server_port) {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        throw std::runtime_error("Creazione socket fallita");
    }

    memset(&servaddr, 0, sizeof(servaddr)); // Equivalente al byteZero in C, pulisce la struttura impostando tutti i byte a zero
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);
    servaddr.sin_addr.s_addr = inet_addr(server_ip.c_str());
}

// Implementazione Distruttore
UDPClient::~UDPClient() {
    if (sockfd >= 0) {
        close(sockfd);
        std::cout << "Socket chiuso." << std::endl;
    }
}

// Implementazione sendMessage
void UDPClient::sendMessage(std::string message) {
    sendto(sockfd, message.c_str(), message.length(), MSG_CONFIRM,
           (const struct sockaddr *)&servaddr, sizeof(servaddr));
}

// Implementazione receiveMessage
std::string UDPClient::receiveMessage() {
    char buffer[MAXLINE];
    socklen_t len = sizeof(servaddr);

    ssize_t n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL,
                     (struct sockaddr *)&servaddr, &len);
    
    if (n < 0) return ""; // O gestisci errore

    buffer[n] = '\0';
    return std::string(buffer);
}