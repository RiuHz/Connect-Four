#include "messaggio.h"

Messaggio creaMessaggio(MessageType tipo, uint32_t dimensione, uint32_t * payload) {
    Messaggio messaggio;

    messaggio.header.type = tipo;
    messaggio.header.length = dimensione;
    messaggio.payload = payload;

    return messaggio;
}

void eliminaMessaggio(Messaggio * messaggio) {
    free(messaggio -> payload);

    messaggio -> payload = NULL;
}
