#include "partita.h"

Partita * creaPartita(unsigned int id, Client * proprietario) {

    Partita * partita = malloc(sizeof(Partita));

    partita -> id = id;

    partita -> proprietario = proprietario;
    partita -> avversario = NULL;

    partita -> next = NULL;

    return partita;
}

void aggiungiProprietario(Partita * partita, Client * proprietario) {
    partita -> proprietario = proprietario;
}

void aggiungiAvversario(Partita * partita, Client * avversario) {
    partita -> avversario = avversario;
}

void aggiungiMossa(Partita *partita, int colonna, unsigned int simbolo){
    // si prende la board della partita
    // si cicla sulle rows finche non trova un valore a 0 
    // e inserisce come valore il simbolo
    
    for(int numeroRiga=1;numeroRiga<=BOARD_ROWS;numeroRiga++){
        if(partita->board[numeroRiga][colonna]==0){
            partita->board[numeroRiga][colonna]=simbolo;
        }
    }
}

unsigned int esitoPartita(Partita *partita,unsigned int simbolo){

    // LEGGENDA FLAG: 0 si continua, 1 vittoria, 2 pareggio

    // logica per capire se una persona ha vinto (ORIZZONTALE)
    if(verificaCombinazioneOrizzontale(partita,simbolo) == 1){
        return 1;
    }
    

    // logica per capire se una persona ha vinto (VERTICALE)
    if(verificaCombinazioneVerticale(partita,simbolo) == 1){
        return 1;
    }

    // logica per capire se una persona ha vinto (DIAGONALE PRINCIPALE)
    if(verificaCombinazioneDiagonalePrincipale(partita,simbolo) == 1){
        return 1;
    }
    
    // logica per capire se una persona ha vinto (DIAGONALE SECONDARIA)
    if(verificaCombinazioneDiagonaleSecondaria(partita,simbolo) == 1){
        return 1;
    }    

    //logica di pareggio alla fine : prima controllo se ci sono combinazioni vincenti e poi verifico la board, se è piena pareggio
    if(verificaPareggio(partita) == 2){
        return 2;
    }

    return 0;

}
unsigned int verificaCombinazioneOrizzontale(Partita *partita,unsigned int simbolo){
    unsigned int contatore=0;

    for(unsigned int numeroRiga=1; numeroRiga<=BOARD_ROWS; numeroRiga++){
        for(unsigned int numeroColonna=1; numeroColonna<=BOARD_COLUMNS; numeroColonna++){
            for(unsigned int gettoneAdiacente=numeroColonna; numeroColonna + 3 <= BOARD_COLUMNS && gettoneAdiacente<=BOARD_COLUMNS && gettoneAdiacente - numeroColonna < 4; gettoneAdiacente++){
                if(partita->board[numeroRiga][gettoneAdiacente]==simbolo){
                    contatore += 1;
                    if(contatore == 4){
                        return 1;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    return 0;
}

unsigned int verificaCombinazioneVerticale(Partita *partita,unsigned int simbolo){
    unsigned int contatore=0;

    for(unsigned int numeroColonna=1; numeroColonna<=BOARD_COLUMNS; numeroColonna++){
        for(unsigned int numeroRiga=1; numeroRiga<=BOARD_ROWS; numeroRiga++){
            for(unsigned int gettoneSuperiore=numeroRiga; numeroRiga + 3 <= BOARD_ROWS && gettoneSuperiore<=BOARD_ROWS && gettoneSuperiore - numeroRiga < 4; gettoneSuperiore++){
                if(partita->board[gettoneSuperiore][numeroRiga]==simbolo){
                    contatore += 1;
                    if(contatore == 4){
                        return 1;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    return 0;
}

unsigned int verificaCombinazioneDiagonalePrincipale(Partita *partita,unsigned int simbolo){
    unsigned int contatore=0;

    for(unsigned int numeroRiga=1; numeroRiga<=BOARD_ROWS - 3; numeroRiga++){
        for(unsigned int numeroColonna=1; numeroColonna<=BOARD_COLUMNS - 3; numeroColonna++){
            for(unsigned int colonnaDiagonale=numeroColonna, rigaDiagonale = numeroRiga; colonnaDiagonale <= BOARD_COLUMNS && rigaDiagonale <= BOARD_ROWS; colonnaDiagonale++, rigaDiagonale++){
                if(partita->board[rigaDiagonale][colonnaDiagonale]==simbolo){
                    contatore += 1;
                    if(contatore == 4){
                        return 1;
                    }
                }
                else
                {
                    break;
                }
            }
        }    
    }
}

unsigned int verificaCombinazioneDiagonaleSecondaria(Partita *partita,unsigned int simbolo){
    unsigned int contatore=0;

    for(unsigned int numeroRiga=4; numeroRiga<=BOARD_ROWS; numeroRiga++){
        for(unsigned int numeroColonna=1; numeroColonna<=BOARD_COLUMNS - 3; numeroColonna++){
            for(unsigned int colonnaDiagonale=numeroColonna, rigaDiagonale = numeroRiga; colonnaDiagonale <= BOARD_COLUMNS && rigaDiagonale >= 1; colonnaDiagonale++, rigaDiagonale--){
                if(partita->board[rigaDiagonale][colonnaDiagonale]==simbolo){
                    contatore += 1;
                    if(contatore == 4){
                        return 1;
                    }
                }
                else
                {
                    break;
                }
            }
        }    
    }
}

unsigned int verificaPareggio(Partita *partita){
    unsigned int contatore=0;
    
    for(unsigned int numeroRiga=1; numeroRiga<=BOARD_ROWS; numeroRiga++){
        for(unsigned int numeroColonna=1; numeroColonna<=BOARD_COLUMNS; numeroColonna++){
            if(partita->board[numeroRiga][numeroColonna] != 0){
                contatore += 1;
                if(contatore == 42){
                    return 2;
                }
            }
        }
    }

    return 0;
}

void rimuoviProprietario(Partita * partita) {
    partita -> proprietario = NULL;
}


