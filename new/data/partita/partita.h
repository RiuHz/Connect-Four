#ifndef PARTITA_H
#define PARTITA_H

#include "../client/client.h"

typedef struct Partita {
    unsigned int id;
    Client * proprietario;
    Client * avversario;
    Partita * next;
} Partita;

Partita * creaPartita(unsigned int id, Client * proprietario);

void aggiungiProprietario(Partita * partita, Client * proprietario);
void aggiungiAvversario(Partita * partita, Client * avversario);

void rimuoviProprietario(Partita * partita);

#endif
