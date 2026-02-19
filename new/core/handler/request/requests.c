#include "requests.h"

Messaggio richiestaConnessione(uint32_t * payload) {
    Messaggio messaggio;

    messaggio.tipo = REQ_CONNECT;
    messaggio.payload = malloc(sizeof(Payload_REQ_CONNECT));

    strcpy(((Payload_REQ_CONNECT *) messaggio.payload) -> nome, (char *) payload);

    return messaggio;
}

Messaggio richiestaDisconnessione() {
    Messaggio messaggio;

    messaggio.tipo = REQ_DISCONNECT;
    messaggio.payload = NULL;

    return messaggio;
}

Messaggio richiestaCreaPartita() {
    Messaggio messaggio;

    messaggio.tipo = REQ_CREATE_GAME;
    messaggio.payload = NULL;

    return messaggio;
}

Messaggio richiestaPartecipaPartita(uint32_t * payload) {
    Messaggio messaggio;

    messaggio.tipo = REQ_JOIN_GAME;
    messaggio.payload = malloc(sizeof(unsigned int));

    *(unsigned int *) messaggio.payload = ntohl(* payload);

    return messaggio;
}

Messaggio richiestaLasciaPartita() {
    Messaggio messaggio;

    messaggio.tipo = REQ_LEAVE_GAME;
    messaggio.payload = NULL;

    return messaggio;
}

Messaggio richiestaAccettaPartita() {
    Messaggio messaggio;

    messaggio.tipo = REQ_GAME_ACCEPTED;
    messaggio.payload = NULL;

    return messaggio;
}

Messaggio richiestaRifiutaPartita() {
    Messaggio messaggio;

    messaggio.tipo = REQ_GAME_DENIED;
    messaggio.payload = NULL;

    return messaggio;
}

Messaggio richiestaListaPartite() {
    Messaggio messaggio;

    messaggio.tipo = REQ_GAMES_LIST;
    messaggio.payload = NULL;

    return messaggio;
}

Messaggio richiestaMossa(uint32_t * payload) {
    Messaggio messaggio;

    messaggio.tipo = REQ_MOVE;
    messaggio.payload = malloc(sizeof(unsigned int));

    *(unsigned int *) messaggio.payload = ntohl(* payload);
}

Messaggio richiestaAccettaRivincita() {
    Messaggio messaggio;

    messaggio.tipo = REQ_REMATCH_ACCEPTED;
    messaggio.payload = NULL;

    return messaggio;
}

Messaggio richiestaRifiutaRivincita() {
    Messaggio messaggio;

    messaggio.tipo = REQ_REMATCH_DENIED;
    messaggio.payload = NULL;

    return messaggio;
}
