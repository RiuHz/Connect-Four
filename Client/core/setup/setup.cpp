#include "setup.hpp"

namespace lso {

    std::string Setup::getPlayerName() noexcept {
        lso::Screen::clear();

        std::string playerName;

        std::cout << "Inserisci il tuo nome"
                << std::endl
                << "> ";
        std::cin >> playerName;


        return playerName;
    }

    void Setup::connectToServer() {
        lso::Screen::clear();

        auto test = []() -> void {
            std::this_thread::sleep_for(std::chrono::seconds(10));
        };

        Spinner::showLoadingTextOnFunction<void>(std::string("Connessione al server"), test);
    }

}
