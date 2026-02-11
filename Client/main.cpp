#include <string>

#include "core/setup/setup.hpp"
#include "core/board/board.hpp"
#include "headers/UDPClient.hpp"

using namespace std;

int main() {

    /* Socket UDP */
    try {
        UDPClient client("127.0.0.1", 5000);

        client.sendMessage("Ciao sono il client 123");
        
        std::cout << "Messaggio inviato. Attendo risposta..." << std::endl;
        
        std::string risposta = client.receiveMessage();
        std::cout << "Risposta dal Server C: " << risposta << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    string player_name = lso::Setup::getPlayerName();

    lso::Setup::connectToServer();


    // Mostra lista lobby

    /*
    1) Pulire console
    2) Idea presa da whiteboard
    3) Input nel rigo più basso della console?
    */

    // Test Board

    cout << "Printing empty board" << endl;

    lso::Board board = lso::Board();

    board.printBoard();

    cout << endl << endl;
    
    board.addRedMove(1);
    board.printBoard();

    cout << endl << endl;

    board.addYellowMove(1);
    board.printBoard();

    for (int i = 0; i < 6; i++) {
        cout << endl << endl;

        board.addYellowMove(1);
        board.printBoard();
    }

    try {
        board.addRedMove(1);
    } catch (std::exception error) {
        cout << error.what() << endl;
    }


    return 0;
}
