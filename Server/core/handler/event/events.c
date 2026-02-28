#include "events.h"

Messaggio eventoAggiornamentoListaPartite(ListaPartite * lista) {
    unsigned int dimensione = sizeof(Game) * lista -> contatore / sizeof(unsigned int);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    for (Partita * partita = lista -> head; partita != NULL; partita = partita -> next) {
        Game game = serializzaPartita(partita);

        buffer[offset++] = game.id;

        memcpy(& buffer[offset], game.proprietario, NAME_LEN);
        offset += (NAME_LEN + 3) / 4;

        memcpy(& buffer[offset], game.avversario, NAME_LEN);
        offset += (NAME_LEN + 3) / 4;

        buffer[offset++] = game.stato;
    }
    
    return creaMessaggio(EVT_GAMES_LIST_UPDATED, dimensione, buffer);
}

Messaggio eventoPartitaCreata(Partita * partita) {
    Game game = serializzaPartita(partita);
    
    unsigned int dimensione = sizeof(Game) / sizeof(uint32_t);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    buffer[offset++] = game.id;

    memcpy(& buffer[offset], game.proprietario, NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    memcpy(& buffer[offset], game.avversario, NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    buffer[offset++] = game.stato;

    return creaMessaggio(EVT_GAME_CREATED, dimensione, buffer);
}

Messaggio eventoPartitaTerminata(unsigned int id) {
    unsigned int dimensione = sizeof(unsigned int);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    buffer[offset++] = htonl(id);

    return creaMessaggio(EVT_GAME_CREATED, dimensione, buffer);
}

Messaggio eventoAggiornamentoBoard(Partita * partita) {
    Board board = serializzaBoard(partita);

    unsigned int dimensione = sizeof(Board) / sizeof(uint32_t);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    for (uint32_t row = 0; row < BOARD_ROWS; row++) {
        for (uint32_t column = 0; column < BOARD_COLUMNS; column++) {
            buffer[offset++] = board.grid[row][column];
        }
    }

    return creaMessaggio(EVT_UPDATE_BOARD, dimensione, buffer);
}
