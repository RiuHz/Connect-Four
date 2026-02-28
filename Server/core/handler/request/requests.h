#ifndef REQUESTS_H
#define REQUESTS_H

#include <arpa/inet.h>

#include "../../../model/client/client.h"

#include "../../../network/shared/protocol.h"

void richiestaConnessione(Client * client, uint32_t * payload);

unsigned int richiestaPartecipaPartita(uint32_t * payload);

unsigned int richiestaRispostaAccessoPartita(uint32_t * payload);

unsigned int richiestaMossa(uint32_t * payload);

unsigned int richiestaRivincita(uint32_t * payload);

#endif
