#include <iostream>
#include <vector>
#include "enum/TextColors.hpp"
#include "enum/TextStyles.hpp"
#include "headers/UDPClient.hpp"

using namespace lso;

// Definire il tipo board e uint oppure mi sparo

// Devo pensare che la board arriva già colorata, quindi devo usare il tipo String

void printRow(const std::vector<std::vector<std::string>> & board, const unsigned int row, const unsigned int cols) {
    std::cout << TextColor::BLUE << '|' << TextColor::WHITE;

    for (unsigned int i = 0; i < cols; i++)
        std::cout << " " << board[row][i] << " ";

    std::cout << TextColor::BLUE << '|' << TextColor::WHITE << std::endl;
}

void printSeparator(const unsigned int cols) {
    std::cout << TextColor::BLUE << '+';

    for (unsigned int i = 0; i < cols; i++)
        std::cout << "---";

    std::cout << '+' << TextColor::WHITE << std::endl;
}

void printColumNumbers(const unsigned int cols) {
    std::cout << TextColor::BLUE << '|' << TextColor::WHITE;

    for (unsigned int i = 0; i < cols; i++) {
        std::cout << ' ' << i << ' ';
    }

    std::cout << TextColor::BLUE << '|' << TextColor::WHITE << std::endl;
}

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

    unsigned int rows = 6;
    unsigned int cols = 7;

    std::vector<std::vector<std::string>> board(rows, std::vector<std::string>(cols, "·"));

    board[5][0] = TextColor::RED + (TextStyle::BOLD + std::string("X")) + TextStyle::RESET;
    board[5][1] = TextColor::YELLOW + (TextStyle::BOLD + std::string("O")) + TextStyle::RESET;

    for (unsigned int i = 0; i < rows; i++)
        printRow(board, i, cols);

    printSeparator(cols);
    printColumNumbers(cols);

    return 0;
}
