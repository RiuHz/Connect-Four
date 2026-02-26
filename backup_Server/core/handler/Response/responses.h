#ifndef RESPONSES_H
#define RESPONSES_H

#include "../../global/globals.h"

void rispostaConnessione(ClientInfo *clientConnesso);
void rispostaCreaPartita(ClientInfo *clientConnesso);
void rispostaListaPartite(ClientInfo *clientConnesso, size_t dimensioneDaInviare, Payload_RES_GAMES_LIST *listaPartiteDaInviare );

#endif