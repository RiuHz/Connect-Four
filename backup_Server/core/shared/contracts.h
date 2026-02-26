#ifndef CONTRACTS_H
#define CONTRACTS_H

#include <stdint.h> // Garantisce che le struct da un pc all' altro abbiano sempre la stessa dimensione fissa

// Definizione dei tipi (Codici)
// LEGGENDA (da chi viene usato il pacchetto per mandare ?): C=CLIENT, S=SERVER 
#define C_BENVENUTO 1
#define S_BENVENUTO 2

#define CREA_PARTITA 3
#define LISTA_PARTITE 4
#define ALERT_NUOVA_PARTITA 5

// Definizione delle strutture di gioco 

typedef struct __attribute__((packed)) { // __attribute__((packed)) assicura che non ci siano "buchi" tra i byte.
    uint8_t  tipoMessaggio;  
    char     nomeGiocatore[20];
} C_Benvenuto;

typedef struct __attribute__((packed)) { // __attribute__((packed)) assicura che non ci siano "buchi" tra i byte.
    uint8_t  tipoMessaggio;  
    char     messaggioBenvenuto[100];
} S_Benvenuto;

#endif