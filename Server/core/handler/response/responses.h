#ifndef RESPONSES_H
#define RESPONSES_H

#include <arpa/inet.h>

#include "../../../data/list/list.h"

#include "../../../network/messaggio/messaggio.h"
#include "../../../network/shared/protocol.h"

Messaggio rispostaCreaPartita(Partita * partita);

Messaggio rispostaAccessoPartita(unsigned int risposta);

Messaggio rispostaListaPartite(ListaPartite * lista);

Messaggio rispostaRivincita(unsigned int risposta);

#endif
