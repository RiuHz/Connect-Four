#include "responses.h"


Messaggio rispostaCreaPartita(Partita * partita) {
    Game game = serializzaPartita(partita);
    
    uint32_t * buffer = malloc(sizeof(Game) / sizeof(uint32_t));
    unsigned int offset = 0;

    buffer[offset++] = game.id;

    memcpy(& buffer[offset], game.proprietario, NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    memcpy(& buffer[offset], game.avversario, NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    buffer[offset++] = game.stato;

    return creaMessaggio(RES_CREATE_GAME, buffer);
}

Messaggio rispostaAccessoPartita(unsigned int risposta) {
    uint32_t * buffer = malloc(sizeof(unsigned int));
    unsigned int offset = 0;

    buffer[offset++] = htonl(risposta);

    return creaMessaggio(RES_JOIN_GAME, buffer);
}

Messaggio rispostaListaPartite(ListaPartite * lista){
    uint32_t * buffer = malloc(sizeof(Game) * lista -> contatore / sizeof(unsigned int));
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
    
    return creaMessaggio(RES_GAMES_LIST, buffer);
}

Messaggio rispostaRivincita(unsigned int risposta) {
    uint32_t * buffer = malloc(sizeof(unsigned int));
    unsigned int offset = 0;

    buffer[offset++] = htonl(risposta);

    return creaMessaggio(RES_REMATCH, buffer);
}
