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

void rimuoviProprietario(Partita * partita) {
    partita -> proprietario = NULL;
}
