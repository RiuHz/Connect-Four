#include "requests.h"

void richiestaConnessione(Client * client, uint32_t * payload) {
    memcpy(client -> nome, payload, NAME_LEN);
}

unsigned int richiestaPartecipaPartita(uint32_t * payload) {
    unsigned int idPartita = * payload;

    return idPartita;
}

unsigned int richiestaRispostaAccessoPartita(uint32_t * payload) {
    unsigned int risposta = * payload;

    return risposta;
}

unsigned int richiestaMossa(uint32_t * payload) {
    unsigned int colonna = * payload;

    return colonna;
}

unsigned int richiestaRivincita(uint32_t * payload) {
    unsigned int rivincita = * payload;

    return rivincita;
}
