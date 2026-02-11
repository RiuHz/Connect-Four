#include <string>

#include "core/setup/setup.hpp"
#include "core/board/board.hpp"

using namespace std;

int main() {

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
