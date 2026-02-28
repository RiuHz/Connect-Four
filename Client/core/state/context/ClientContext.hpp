#ifndef CLIENT_CONTEXT_HPP
#define CLIENT_CONTEXT_HPP

#include <memory>
#include <string>
#include <iostream>

#include "../State.hpp"
#include "../../../network//tcp/TCPClient.hpp" 
#include "../../../network/packet/PacketBuilder.hpp"


/*  è la classe responsabile ai salvataggi dei dati da uno stato all' altro, 
    deve contenere tutto ciò che dobbiamo conservare 
    (nome del giocatore, la connession, ecc) 
*/
class ClientContext {
private:
    std::unique_ptr<State> currentState;
    bool isRunning;

    std::string playerName;
    
    TCPClient tcpClient; 

public:
    ClientContext(std::unique_ptr<State> initialState);
    void transitionTo(std::unique_ptr<State> nextState);
    void run();
    void stop();

    void setPlayerName(const std::string& name) { playerName = name; }
    std::string getPlayerName() const { return playerName; }

    TCPClient* getNetwork() { return &tcpClient; }
};

#endif