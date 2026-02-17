#ifndef GLOBALS_H
#define GLOBALS_H

#include "../utils/list.h"
#include <pthread.h>
#include "../shared/protocol.h"

typedef struct ListaClient {
        int socketClient;
        struct ListaClient *next;
} ListaClient;

typedef struct ListaPartite {
        Game game;
        struct ListaPartite *next;
} ListaPartite;


// Dichiarazioni
extern pthread_mutex_t mutexListaClient; 
extern ListaClient* listaClient;

extern pthread_mutex_t mutexListaPartite; 
extern ListaPartite* listaPartite;

#endif