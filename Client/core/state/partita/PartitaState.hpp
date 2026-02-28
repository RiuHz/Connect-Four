#ifndef PARTITA_STATE_HPP
#define PARTITA_STATE_HPP

#include "../State.hpp"
#include "../menu/MenuState.hpp"
#include "../context/ClientContext.hpp"
#include <iostream>


class PartitaState : public State {
public:
    void onEnter(ClientContext* context) override;
    void handleUserInput(ClientContext* context, const std::string& input) override;
};

#endif