#ifndef REQUETS_H
#define REQUETS_H

#include "../../global/globals.h"

void richiestaConnessione(ClientInfo *clientConnesso,uint32_t dimensionePayloadDaLeggere);
void richiestaCreaPartita(ClientInfo *clientConnesso);
void richiestaListaPartite(ClientInfo *clientConnesso);

#endif