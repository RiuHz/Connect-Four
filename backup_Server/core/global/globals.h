#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>

#include "../utils/list.h"

#include "../shared/protocol.h"

typedef struct ClientInfo {
        int socketClient;
        char nomeClient[21];
} ClientInfo;

typedef struct Partita {
        uint32_t id;
        int socketProprietario;
        char proprietario[NAME_LEN];
        int socketAvversario;
        char avversario[NAME_LEN];
        uint32_t stato;
} Partita;

// Dichiarazioni delle liste per mandare i dati in broadcast 
typedef struct ListaClient {
        int socketClient;
        struct ListaClient *next;
} ListaClient;

// Lista ibrida sia per client che server (quando le mando al client escludo le socket)
typedef struct ListaPartite {
        Partita partita;
        struct ListaPartite *next;
} ListaPartite;

// Dichiarazioni variabili
extern pthread_mutex_t mutexListaClient; 
extern ListaClient* listaClient;

extern pthread_mutex_t mutexListaPartite; 
extern ListaPartite* listaPartite;

extern pthread_mutex_t mutexNumeroPartita; 
extern uint32_t numeroPartita;

uint32_t ottieniNuovoIdentificativoPartita();


#endif