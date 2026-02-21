#ifndef PARTITA_H
#define PARTITA_H

#include "../client/client.h"
#include <pthread.h>
#include "../../network/shared/protocol.h"

#define SIMBOLO_PROPRIETARIO 1
#define SIMBOLO_AVVERSARIO 2

typedef struct Partita {
    unsigned int id;
    Client * proprietario;
    Client * avversario;
    pthread_mutex_t mutex;
    unsigned int board[BOARD_ROWS][BOARD_COLUMNS];
    Partita * next;
} Partita;

Partita * creaPartita(unsigned int id, Client * proprietario);

void aggiungiProprietario(Partita * partita, Client * proprietario);
void aggiungiAvversario(Partita * partita, Client * avversario);

void aggiungiMossa(Partita *partita, int colonna, unsigned int simbolo);
void aggiungiMossaProprietario(Partita *partita, unsigned int colonna){aggiungiMossa(partita, colonna, SIMBOLO_PROPRIETARIO);}
void aggiungiMossaAvversario(Partita *partita, unsigned int colonna){aggiungiMossa(partita, colonna, SIMBOLO_AVVERSARIO);}

unsigned int esitoPartita(Partita *partita,unsigned int simbolo); // 2 diagonali, orzziontale e verticale (capire come avvisare chi ha vinto, nella stessa funzione?) 
unsigned int verificaCombinazioneOrizzontale(Partita *partita,unsigned int simbolo); 
unsigned int verificaCombinazioneVerticale(Partita *partita,unsigned int simbolo); 
unsigned int verificaCombinazioneDiagonalePrincipale(Partita *partita,unsigned int simbolo);
unsigned int verificaCombinazioneDiagonaleSecondaria(Partita *partita,unsigned int simbolo); 
unsigned int verificaPareggio(Partita *partita); 

void rimuoviProprietario(Partita * partita);

#endif
