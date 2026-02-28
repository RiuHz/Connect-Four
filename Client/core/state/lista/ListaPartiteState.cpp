#include "ListaPartiteState.hpp"


void ListaPartiteState::onEnter(ClientContext* /*context*/) {
    std::cout << "\n=== LISTA DELLE PARTITE ===\n";
    std::cout << "Qui in futuro appariranno le partite disponibili dal server...\n";
    std::cout << "Scrivi 'esci' per tornare al Menu Principale.\n> ";
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