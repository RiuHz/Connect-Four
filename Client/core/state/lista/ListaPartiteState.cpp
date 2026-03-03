#include "ListaPartiteState.hpp"


void ListaPartiteState::onEnter(ClientContext* /*context*/) {
    std::cout << "=== LISTA DELLE PARTITE ===" << std::endl
        << "Qui in futuro appariranno le partite disponibili dal server...\n"
        << "Scrivi 'esci' per tornare al Menu Principale." << std::endl;
}

void ListaPartiteState::handleUserInput(ClientContext* context, const std::string& input) {
    if (input == "esci") {
        // L'utente vuole tornare indietro: cambiamo stato passando al Menu
        context->transitionTo(std::make_unique<MenuState>());
    } else {
        // Se l'utente scrive altro, gli diciamo che il comando non è valido
        std::cout << "Comando non riconosciuto in questa schermata. Scrivi 'esci' per tornare indietro.\n> ";
    }
}