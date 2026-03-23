#include "events.h"

Messaggio eventoRichiestaPartecipazione(Client * client) {
    unsigned int dimensione = ((NAME_LEN + 3) / 4) * 4;
    uint32_t * buffer = malloc(dimensione);

    memcpy(buffer, client -> nome, NAME_LEN);

    return creaMessaggio(EVT_JOIN_REQUEST, dimensione, buffer);
}

Messaggio eventoAggiornamentoPartita(Partita * partita) {
    Game game = serializzaPartita(partita);
    
    unsigned int dimensione = sizeof(Game);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    buffer[offset++] = game.id;

    memcpy(& buffer[offset], game.proprietario, NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    memcpy(& buffer[offset], game.avversario, NAME_LEN);
    offset += (NAME_LEN + 3) / 4;
    
    return creaMessaggio(EVT_GAME_UPDATE, dimensione, buffer);
}

Messaggio eventoPartitaCreata(Partita * partita) {
    Game game = serializzaPartita(partita);
    
    unsigned int dimensione = sizeof(Game);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    buffer[offset++] = game.id;

    memcpy(& buffer[offset], game.proprietario, NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    memcpy(& buffer[offset], game.avversario, NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    return creaMessaggio(EVT_GAME_CREATED, dimensione, buffer);
}

Messaggio eventoPartitaTerminata(unsigned int id) {
    unsigned int dimensione = sizeof(unsigned int);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    buffer[offset++] = id;

    return creaMessaggio(EVT_GAME_ENDED, dimensione, buffer);
}

Messaggio eventoAggiornamentoBoard(Partita * partita) {
    Board board = serializzaBoard(partita);

    unsigned int dimensione = sizeof(Board);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    for (uint32_t row = 0; row < BOARD_ROWS; row++) {
        for (uint32_t column = 0; column < BOARD_COLUMNS; column++) {
            buffer[offset++] = board.grid[row][column];
        }
    }

    return creaMessaggio(EVT_UPDATE_BOARD, dimensione, buffer);
}
