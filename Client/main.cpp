#include <string>

#include "components/screen/screen.hpp"

#include "core/game/game.hpp"
#include "network/tcp/TCPClient.hpp"
#include "setup/setup.hpp"

#include "core/enum/TextStyles.hpp"

#include "core/state/context/ClientContext.hpp"
#include "core/state/login/LoginState.hpp"

using namespace std;

int main() {
    // Creiamo il client partendo dal Menu
    ClientContext clientConnesso(std::make_unique<LoginState>());
    
    // Avviamo il loop del gioco (esco quando invoco clientConnesso.stop())
    clientConnesso.run();

    return 0;
}
