#include "partita.h"

Partita * creaPartita(unsigned int id, Client * proprietario) {

    Partita * partita = malloc(sizeof(Partita));

    partita -> id = id;

    partita -> proprietario = proprietario;
    partita -> avversario = NULL;

    memset(partita -> board, 0, sizeof(partita -> board));
    
    partita -> stato = GAME_WAITING;

    partita -> next = NULL;

    return partita;
}

void aggiungiProprietario(Partita * partita, Client * proprietario) {
    partita -> proprietario = proprietario;
}

void aggiungiAvversario(Partita * partita, Client * avversario) {
    partita -> avversario = avversario;
}

void rimuoviProprietario(Partita * partita) {
    partita -> proprietario = NULL;
}

bool controllaValiditaMossa(Partita * partita, unsigned int colonna) {
    return colonna < BOARD_COLUMNS && partita -> board[0][colonna] == 0;
}

void aggiungiMossa(Partita *partita, unsigned int colonna, unsigned int simbolo) {    
    for (unsigned int riga = 0; riga < BOARD_ROWS; riga++) {
        if (partita -> board[riga][colonna] == 0) {
            partita -> board[riga][colonna] = simbolo;
            break;
        }
    }
}

void aggiungiMossaProprietario(Partita *partita, unsigned int colonna) {
    aggiungiMossa(partita, colonna, SIMBOLO_PROPRIETARIO);
}

void aggiungiMossaAvversario(Partita *partita, unsigned int colonna) {
    aggiungiMossa(partita, colonna, SIMBOLO_AVVERSARIO);
}

EsitoPartita controllaEsitoPartita(Partita * partita, unsigned int simbolo) {

    if (verificaCombinazioneOrizzontale(partita,simbolo)) {
        return VITTORIA;
    }
    
    if (verificaCombinazioneVerticale(partita,simbolo)) {
        return VITTORIA;
    }

    if (verificaCombinazioneDiagonale(partita,simbolo)) {
        return VITTORIA;
    }

    if (verificaPareggio(partita)) {
        return PAREGGIO;
    }

    return NON_TERMINATA;
}

bool verificaCombinazioneOrizzontale(Partita * partita, unsigned int simbolo) {

    for (unsigned int riga = 0; riga < BOARD_ROWS; riga++) {
        for (unsigned int colonna = 0; colonna < BOARD_COLUMNS - 3; colonna++) {
            if (
                partita -> board[riga][colonna] == simbolo &&
                partita -> board[riga][colonna] == partita -> board[riga][colonna + 1] == partita -> board[riga][colonna + 2] == partita -> board[riga][colonna + 3]
            ) {
                return true;
            } 
        }
    }

    return false;
}

bool verificaCombinazioneVerticale(Partita *partita,unsigned int simbolo){

    for (unsigned int colonna = 0; colonna < BOARD_COLUMNS; colonna++) {
        for (unsigned int riga = 0; riga < BOARD_ROWS - 3; riga++) {
            if (
                partita -> board[riga][colonna] == simbolo &&
                partita -> board[riga][colonna] == partita -> board[riga + 1][colonna] == partita -> board[riga + 2][colonna] == partita -> board[riga + 3][colonna ]
            ) {
                return true;
            } 
        }
    }

    return false;
}

bool verificaCombinazioneDiagonale(Partita * partita, unsigned int simbolo) {
    return verificaCombinazioneDiagonalePrincipale(partita, simbolo) || verificaCombinazioneDiagonaleSecondaria(partita, simbolo);
}

bool verificaCombinazioneDiagonalePrincipale(Partita *partita,unsigned int simbolo){

    for (unsigned int riga = 3; riga < BOARD_ROWS; riga++) {
        for (unsigned int colonna = 0; colonna < BOARD_COLUMNS - 3; colonna++) {
            if (
                partita -> board[riga][colonna] == simbolo &&
                partita -> board[riga][colonna] == partita -> board[riga - 1][colonna + 1] == partita -> board[riga - 2][colonna + 2] == partita -> board[riga - 3][colonna + 3]
            ) {
                return true;
            }
        }
    }

    return false;
}

bool verificaCombinazioneDiagonaleSecondaria(Partita *partita,unsigned int simbolo){
       
    for (unsigned int riga = 0; riga < BOARD_ROWS - 3; riga++) {
        for (unsigned int colonna = 0; colonna < BOARD_COLUMNS - 3; colonna++) {
            if (
                partita -> board[riga][colonna] == simbolo &&
                partita -> board[riga][colonna] == partita -> board[riga + 1][colonna + 1] == partita -> board[riga + 2][colonna + 2] == partita -> board[riga + 3][colonna + 3]
            ) {
                return true;
            }
        }
    }

    return false;
}

bool verificaPareggio(Partita * partita) {
    unsigned int primaRiga = 0;
    
    for (unsigned int colonna = 0; colonna < BOARD_COLUMNS; colonna++) {
        if (partita -> board[primaRiga][colonna] == 0) {
            return false;
        }
    }

    return true;
}

Game serializzaPartita(Partita * partita) {
    Game game;

    game.id = htonl(partita -> id);
    strcpy(game.proprietario, partita -> proprietario -> nome);
    strcpy(game.avversario, partita -> avversario -> nome);
    game.stato = htonl(partita -> stato);

    return game;
}

Board serializzaBoard(Partita * partita) {
    Board board;

    for (unsigned int row = 0; row < BOARD_ROWS; row++) {
        for (unsigned int column = 0; column < BOARD_COLUMNS; column++) {
            board.grid[row][column] = partita -> board[row][column];
        }
    }

    return board;
}
