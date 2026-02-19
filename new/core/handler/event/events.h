#ifndef RESPONSES_H
#define RESPONSES_H

#include "../../network/messaggio/messaggio.h"
#include "../../network/shared/protocol.h"

#include <stdlib.h>

Messaggio eventoPartitaCreata(Game partitaCreata);
Messaggio eventoPartitaAccettata();
Messaggio eventoPartitaRifiutata();
Messaggio eventoPartitaTerminata(Game partitaTerminata);
Messaggio eventoMossaAvversario(uint32_t mossaAvversario);
Messaggio eventoPartitaVinta();
Messaggio eventoPartitaPersa();
Messaggio eventoPartitaPareggio();
Messaggio eventoRivincitaAccettata();
Messaggio eventoRivincitaRifiutata();
Messaggio eventoAggiornamentoListaPartite(Game partitaDaAggiornare);

#endif
