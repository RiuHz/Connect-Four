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

    unsigned short int scelta = 0;

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
                lso::Screen::briefDisplay("Richiesta crea partita in corso...");
                client -> sendMessage(lso::Message(REQ_CREATE_GAME));
                // Spostare il client nello stato di Partita
                break;

            case 2:
                lso::Screen::briefDisplay("Richiesta lista partite in corso...");
                client -> sendMessage(lso::Message(REQ_GAMES_LIST));
                // Spostare il client nello stato di Lista partite
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
