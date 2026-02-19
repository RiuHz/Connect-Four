#ifndef RESPONSES_H
#define RESPONSES_H

#include "../../data/list/list.h"

void rispostaConnessione();
void rispostaCreaPartita(unsigned int id);
void rispostaListaPartite(ListaPartite * lista, unsigned int lunghezza);

#endif