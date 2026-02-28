#ifndef LOGIN_STATE_HPP
#define LOGIN_STATE_HPP

#include  "../State.hpp"

#include "../menu/MenuState.hpp"
#include "../context/ClientContext.hpp"
#include "../../../network/shared/protocol.h"
#include "../../../network/packet/PacketBuilder.hpp"


#include <iostream>
#include <string>
#include <cstdint> 

class LoginState : public State {
public:
    void onEnter(ClientContext* context) override;
    void handleUserInput(ClientContext* context, const std::string& input) override;
};

#endif