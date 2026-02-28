#include "responses.h"

Messaggio rispostaCreaPartita(Partita * partita) {
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

    return creaMessaggio(RES_CREATE_GAME, dimensione, buffer);
}

Messaggio rispostaAccessoPartita(unsigned int risposta) {
    unsigned int dimensione = sizeof(unsigned int);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    buffer[offset++] = htonl(risposta);

    return creaMessaggio(RES_JOIN_GAME, dimensione, buffer);
}

Messaggio rispostaListaPartite(ListaPartite * lista){
    unsigned int dimensione = (unsigned int) (sizeof(Game) * lista -> contatore / sizeof(unsigned int));
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
    
    return creaMessaggio(RES_GAMES_LIST, dimensione, buffer);
}

Messaggio rispostaRivincita(unsigned int risposta) {
    unsigned int dimensione = sizeof(unsigned int);
    uint32_t * buffer = malloc(dimensione);
    unsigned int offset = 0;

    buffer[offset++] = htonl(risposta);

    return creaMessaggio(RES_REMATCH, dimensione, buffer);
}
