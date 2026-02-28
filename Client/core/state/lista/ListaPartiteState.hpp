#ifndef LISTA_PARTITE_HPP
#define LISTA_PARTITE_HPP

#include "../State.hpp"
#include "../menu/MenuState.hpp" 
#include "../context/ClientContext.hpp"
#include <iostream>

class ListaPartiteState : public State {
public:
    void onEnter(ClientContext* context) override;
    void handleUserInput(ClientContext* context, const std::string& input) override;
};

#endif