#ifndef PARTITA_H
#define PARTITA_H

#include <pthread.h>
#include <stdbool.h>
#include <arpa/inet.h>

#include "../client/client.h"

#include "../../network/shared/protocol.h"

#define SIMBOLO_PROPRIETARIO 1
#define SIMBOLO_AVVERSARIO 2

typedef enum {
    VITTORIA = 1,
    SCONFITTA,
    PAREGGIO,
    NON_TERMINATA
} EsitoPartita;

typedef struct Partita {
    pthread_mutex_t mutex;
    unsigned int id;
    Client * proprietario;
    Client * avversario;
    unsigned int board[BOARD_ROWS][BOARD_COLUMNS];
    GameState stato;
    struct Partita * next;
} Partita;

Partita * creaPartita(unsigned int id, Client * proprietario);

void aggiungiProprietario(Partita * partita, Client * proprietario);
void aggiungiAvversario(Partita * partita, Client * avversario);
void rimuoviProprietario(Partita * partita);

bool controllaValiditaMossa(Partita * partita, unsigned int colonna);

void aggiungiMossa(Partita * partita, unsigned int colonna, unsigned int simbolo);
void aggiungiMossaProprietario(Partita * partita, unsigned int colonna);
void aggiungiMossaAvversario(Partita * partita, unsigned int colonna);

EsitoPartita controllaEsitoPartita(Partita * partita, unsigned int simbolo);

bool verificaCombinazioneOrizzontale(Partita * partita, unsigned int simbolo); 
bool verificaCombinazioneVerticale(Partita * partita, unsigned int simbolo);

bool verificaCombinazioneDiagonale(Partita * partita, unsigned int simbolo);
bool verificaCombinazioneDiagonalePrincipale(Partita * partita, unsigned int simbolo);
bool verificaCombinazioneDiagonaleSecondaria(Partita * partita, unsigned int simbolo); 

bool verificaPareggio(Partita * partita); 

Game serializzaPartita(Partita * partita);
Board serializzaBoard(Partita * partita);

#endif
