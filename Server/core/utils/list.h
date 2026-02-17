#ifndef LIST_H
#define LIST_H
#include "../shared/protocol.h"

void aggiungiClient(int nuovoClientConnesso);
void stampaListaClient();
void rimuoviClient(int clientDisconnesso);

void aggiungiPartitaAllaLista(Game game);
void stampaListaPartite();

#endif