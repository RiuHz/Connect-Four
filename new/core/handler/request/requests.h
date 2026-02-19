#ifndef REQUESTS_H
#define REQUESTS_H

#include "../../data/client/client.h"

#include "../../network/messaggio/messaggio.h"
#include "../../network/shared/protocol.h"

Messaggio richiestaConnessione(uint32_t * payload);
Messaggio richiestaDisconnessione();
Messaggio richiestaCreaPartita();
Messaggio richiestaPartecipaPartita(uint32_t * payload);
Messaggio richiestaLasciaPartita();
Messaggio richiestaAccettaPartita();
Messaggio richiestaRifiutaPartita();
Messaggio richiestaListaPartite();
Messaggio richiestaMossa(uint32_t * payload);
Messaggio richiestaAccettaRivincita();
Messaggio richiestaRifiutaRivincita();

#endif
