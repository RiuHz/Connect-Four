#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "../State.hpp"

#include "../partita/PartitaState.hpp"
#include "../lista/ListaPartiteState.hpp"
#include "../context/ClientContext.hpp"
#include "../option/MenuOption.hpp"
#include <iostream>

/*
lo stato menu non deve sapere nulla su come si fa la connessione al server, si ottiene il nome dal client, niente
deve solo mostrare il menu dopo che l' utente ha fatto il login
*/
class MenuState : public State {
public:
    void onEnter(ClientContext* context) override;
    void handleUserInput(ClientContext* context, const std::string& input) override;
};

#endif