#include "setup.hpp"

namespace lso {

    bool Setup::validPlayerName(const std::string name) noexcept {
        if (name.length() == 0) {
            Screen::briefDisplay("Inserire un nome con almeno un carattere");
            return false;
        }

        if (name.length() >= NAME_LEN) {
            Screen::briefDisplay("Inserire un nome con al massimo " + std::to_string(NAME_LEN - 1) + " caratteri");
            return false;
        }

        return true;
    }

    std::string Setup::getPlayerName() noexcept {
        std::string playerName;

        do {
            Screen::clear();

            std::cout << "Inserisci il tuo nome"
                    << std::endl
                    << "> ";
            std::cin >> playerName;

        } while ( !validPlayerName(playerName) );

        return playerName;
    }

    std::unique_ptr<TCPClient> Setup::connectTCPClient(const std::string name) {
        std::unique_ptr<TCPClient> client = std::make_unique<TCPClient>(SERVER_ADDRESS, SERVER_PORT);

        std::vector<uint32_t> payload(NAME_LEN / sizeof(uint32_t), 0);

        std::memcpy(
            payload.data(),
            name.c_str(),
            std::min(name.size(), static_cast<std::size_t>(NAME_LEN))
        );

        client -> sendMessage(Message(REQ_CONNECT, std::move(payload)));

        return client;
    }

    // Sta funzione fa troppo
    std::unique_ptr<TCPClient> Setup::connectToServer(const std::string name) {
        Screen::clear();

        return Spinner::showLoadingTextOnFunction< std::unique_ptr<TCPClient> >(
            std::string("Connessione al server"),
            connectTCPClient,
            name
        );
    }

}
