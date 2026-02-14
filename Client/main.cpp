#include <string>

#include "core/setup/setup.hpp"
#include "core/network/UDPClient.hpp"
#include "enum/TextStyles.hpp"

#define SERVER_ADDRESS "127.0.0.1"

using namespace std;

void enterAlternateScreen() {
    cout << "\033[?1049h\033[?25l" << flush;
}

void exitAlternateScreen() {
    cout << "\033[?25h\033[?1049l" << flush;
}

void clearScreen() {
    cout << "\033[H\033[2J" << flush;
}

int main() {
    
    try {
        lso::UDPClient client(SERVER_ADDRESS, 5000);

        client.sendMessage("Ciao sono il client 123");
        
        std::cout << "Messaggio inviato. Attendo risposta..." << std::endl;
        
        std::string risposta = client.receiveMessage();
        std::cout << "Risposta dal Server C: " << risposta << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    enterAlternateScreen();

    clearScreen();

    string player_name = lso::Setup::getPlayerName();
    
    clearScreen();

    lso::Setup::connectToServer();

    clearScreen();
    
    int scelta = 0;
    
    do {
        
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
                cout << "Uscendo..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
                
            default:
                cout << "Scelta non valida" << endl;
                this_thread::sleep_for(chrono::seconds(1));
                
        }

        clearScreen();
        
    } while (scelta != 3);

    exitAlternateScreen();

    return 0;
}
