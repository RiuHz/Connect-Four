#include <string>

#include "components/screen/screen.hpp"

#include "core/game/game.hpp"
#include "network/tcp/TCPClient.hpp"
#include "setup/setup.hpp"

#include "core/enum/TextStyles.hpp"

using namespace std;

int main() {

    lso::Screen::open();

    std::string name = lso::Setup::getPlayerName();

    std::unique_ptr<lso::TCPClient> client = lso::Setup::connectToServer(name);

    int scelta = 0;
    
    do {
        
        lso::Screen::clear();

        cout << "|---| Menu |---|" << endl
        << "1) Crea Lobby" << endl
        << "2) Visualizza lobby" << endl
        << "3) Esci" << endl
        << endl
        << "> ";
        
        cin >> scelta;
        
        switch (scelta) {
            case 1:
                // Qua apro la lobby
                cout << "Hai scelto crea lobby" << endl;
                break;
            
            case 2:
                // Qua visualizzo le lobby
                cout << "Hai scelto visualizza lobby" << endl;
                break;
            
            case 3:
                client -> sendMessage(lso::Message(REQ_DISCONNECT));
                lso::Screen::briefDisplay("Uscendo...");
                break;
                
            default:
                lso::Screen::briefDisplay("Scelta non valida");
                
        }
        
    } while (scelta != 3);

    lso::Screen::close();

    return 0;
}
