#include "MenuState.hpp"

MenuOption parseMenuInput(const std::string& input) {
    if (input == "1") return MenuOption::CREATE_MATCH;
    if (input == "2") return MenuOption::LIST_MATCHES;
    if (input == "3") return MenuOption::EXIT;
    
    return MenuOption::INVALID;
}

void MenuState::onEnter(ClientContext* /*context*/ ) {
    std::cout << "\n=== MENU PRINCIPALE ===\n";
    std::cout << "1. Crea Partita\n";
    std::cout << "2. Visualizza Lista Partite\n";
    std::cout << "3. Esci dal gioco\n";
    std::cout << "Scelta: ";
}

void MenuState::handleUserInput(ClientContext* context, const std::string& input) {
    MenuOption scelta = parseMenuInput(input);

    // 2. Facciamo lo switch sull'Enum
    switch (scelta) {
        case MenuOption::CREATE_MATCH:
            context->transitionTo(std::make_unique<PartitaState>());
            break;
            
        case MenuOption::LIST_MATCHES:
            context->transitionTo(std::make_unique<ListaPartiteState>());
            break;
            
        case MenuOption::EXIT:
            std::cout << "Uscita in corso...\n";
            context->stop();
            break;
            
        case MenuOption::INVALID:
        default:
            std::cout << "Scelta non valida. Inserisci 1, 2 o 0.\nScelta: ";
            break;
    }
}

