#include "setup.hpp"

namespace lso {

    std::string Setup::getPlayerName() {
        std::string name;

            std::cout << "Inserisci il tuo nome"
                    << std::endl
                    << "> ";
            std::cin >> name;

        return name;
    }

    void Setup::connectToServer() {
        const char spinner[] = { '|', '/', '-', '\\' };
        const int spinner_len = 4;

        for (unsigned long i = 0; i < 10; i++) {
            std::cout << "\rConnessione al server in corso "
                << spinner[i % spinner_len]
                << std::flush;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "\b"
            << "✔"
            << std::flush;

        std::cout << std::endl;
    }

}
