#ifndef RESPONSES_H
#define RESPONSES_H

#include <stdlib.h>

#include "../../../data/list/list.h"

#include "../../../network/messaggio/messaggio.h"
#include "../../../network/shared/protocol.h"

Messaggio eventoAggiornamentoListaPartite(ListaPartite * lista);

Messaggio eventoPartitaCreata(Partita * partita);
Messaggio eventoPartitaTerminata(unsigned int id);

Messaggio eventoAggiornamentoBoard(Partita * partita);

#endif
