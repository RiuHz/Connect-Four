#include "partita.h"

Partita * creaPartita(unsigned int id, Client * proprietario) {

    Partita * partita = malloc(sizeof(Partita));

    pthread_mutex_init(& partita -> mutex, NULL);
    pthread_cond_init(& partita -> richiesta, NULL);
    partita -> risposta = false;

    partita -> id = id;

    partita -> proprietario = proprietario;
    partita -> avversario = NULL;

    memset(partita -> board, 0, sizeof(partita -> board));
    
    partita -> stato = GAME_WAITING;

    partita -> next = NULL;

    return partita;
}

void aggiungiProprietario(Partita * partita, Client * proprietario) {
    pthread_mutex_lock(& partita -> mutex);

    partita -> proprietario = proprietario;

    pthread_mutex_unlock(& partita -> mutex);
}

void aggiungiAvversario(Partita * partita, Client * avversario) {
    pthread_mutex_lock(& partita -> mutex);

    partita -> avversario = avversario;

    pthread_mutex_unlock(& partita -> mutex);
}

void rimuoviProprietario(Partita * partita) {
    pthread_mutex_lock(& partita -> mutex);

    partita -> proprietario = NULL;

    pthread_mutex_unlock(& partita -> mutex);
}

void rimuoviAvversario(Partita * partita) {
    pthread_mutex_lock(& partita -> mutex);

    partita -> avversario = NULL;

    pthread_mutex_unlock(& partita -> mutex);
}

void scambiaGiocatori(Partita * partita) {
    pthread_mutex_lock(& partita -> mutex);

    Client * temp = partita -> avversario;

    partita -> avversario = partita -> proprietario;
    partita -> proprietario = temp;

    pthread_mutex_unlock(& partita -> mutex);
}

void setRisposta(Partita * partita, bool risposta) {
    pthread_mutex_lock(& partita -> mutex);

    partita -> risposta = risposta;

    pthread_mutex_unlock(& partita -> mutex);
}

bool controllaValiditaMossa(Partita * partita, unsigned int colonna) {
    pthread_mutex_lock(& partita -> mutex);

    return colonna < BOARD_COLUMNS && partita -> board[0][colonna] == CELLA_VUOTA;

    pthread_mutex_unlock(& partita -> mutex);
}

void aggiungiMossa(Partita *partita, unsigned int colonna, unsigned int simbolo) {   
    pthread_mutex_lock(& partita -> mutex);
    
    for (unsigned int riga = 0; riga < BOARD_ROWS; riga++) {
        if (partita -> board[riga][colonna] == CELLA_VUOTA) {
            partita -> board[riga][colonna] = simbolo;
            break;
        }
    }

    pthread_mutex_unlock(& partita -> mutex);
}

void aggiungiMossaProprietario(Partita *partita, unsigned int colonna) {
    aggiungiMossa(partita, colonna, CELLA_PROPRIETARIO);
}

void aggiungiMossaAvversario(Partita *partita, unsigned int colonna) {
    aggiungiMossa(partita, colonna, CELLA_AVVERSARIO);
}

EsitoPartita controllaEsitoPartita(Partita * partita, unsigned int simbolo) {
    pthread_mutex_lock(& partita -> mutex);


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

    pthread_mutex_unlock(& partita -> mutex);

    return NON_TERMINATA;
}

bool verificaCombinazioneOrizzontale(Partita * partita, unsigned int simbolo) {

    for (unsigned int riga = 0; riga < BOARD_ROWS; riga++) {
        for (unsigned int colonna = 0; colonna < BOARD_COLUMNS - 3; colonna++) {
            if (
                partita -> board[riga][colonna] == simbolo &&
                partita -> board[riga][colonna + 1] == simbolo && 
                partita -> board[riga][colonna + 2] == simbolo &&
                partita -> board[riga][colonna + 3] == simbolo
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
                partita -> board[riga + 1][colonna] == simbolo && 
                partita -> board[riga + 2][colonna] == simbolo &&
                partita -> board[riga + 3][colonna ] == simbolo
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
                partita -> board[riga - 1][colonna + 1] == simbolo &&
                partita -> board[riga - 2][colonna + 2] == simbolo &&
                partita -> board[riga - 3][colonna + 3] == simbolo
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
                partita -> board[riga + 1][colonna + 1] == simbolo &&
                partita -> board[riga + 2][colonna + 2] == simbolo && 
                partita -> board[riga + 3][colonna + 3] == simbolo
            ) {
                return true;
            }
        }
    }

    return false;
}

bool verificaPareggio(Partita * partita) {
    pthread_mutex_lock(& partita -> mutex);

    unsigned int primaRiga = 0;
    bool esito = true;
    
    for (unsigned int colonna = 0; colonna < BOARD_COLUMNS; colonna++) {
        if (partita -> board[primaRiga][colonna] == CELLA_VUOTA) {
            esito = false;
            break;
        }
    }

    pthread_mutex_unlock(& partita -> mutex);

    return esito;
}

Game serializzaPartita(Partita * partita) {
    pthread_mutex_lock(& partita -> mutex);

    Game game;

    game.id = partita -> id;

    strcpy(game.proprietario, partita -> proprietario -> nome);
    
    if (partita -> avversario == NULL)
        memset(game.avversario, 0, sizeof(game.avversario));
    else
        strcpy(game.avversario, partita -> avversario -> nome);
    
    game.stato = partita -> stato;

    pthread_mutex_unlock(& partita -> mutex);

    return game;
}

Board serializzaBoard(Partita * partita) {
    pthread_mutex_lock(& partita -> mutex);

    Board board;

    for (unsigned int row = 0; row < BOARD_ROWS; row++) {
        for (unsigned int column = 0; column < BOARD_COLUMNS; column++) {
            board.grid[row][column] = partita -> board[row][column];
        }
    }

    pthread_mutex_unlock(& partita -> mutex);

    return board;
}
