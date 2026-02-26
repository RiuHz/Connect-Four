#ifndef LIST_H
#define LIST_H

#include "../shared/protocol.h"
#include <stddef.h>

typedef struct Partita Partita;

void aggiungiClient(int nuovoClientConnesso);
void stampaListaClient();
void rimuoviClient(int clientDisconnesso);

void aggiungiPartitaAllaLista(Partita partita);
void stampaListaPartite();
Payload_RES_GAMES_LIST* ottieniListaPartite(size_t *dimensioneStruttura);


#endif