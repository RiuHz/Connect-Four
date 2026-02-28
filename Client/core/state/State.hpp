#ifndef STATE_HPP
#define STATE_HPP

#include <string>

class ClientContext;

class State {
public:
    
    virtual ~State() = default;

    /* 
        Facciamo la stampa in base al tipo di stato in cui ci troviamo:
            Menu: stampo il menu iniziale aspettando una richiesta
            Partita: Invio richiesta creazione partita, bla bla bla
            Lobby: Tutto ciò dedicato alla partita in corso
            Lista: Invio richiesta partite globali, bla bla bla
    */
    virtual void onEnter(ClientContext* context) = 0;

    // Metodo per processare le scelte effettuate dall' utente in quel determinato stato
    virtual void handleUserInput(ClientContext* context, const std::string& input) = 0;

    // Metodo per elaborare i pacchetti che arrivano dal server
    // virtual void handleNetwork(ClientContext* context) = 0;
};

#endif