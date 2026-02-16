#ifndef GLOBALS_H
#define GLOBALS_H

#include "../utils/list.h"
#include <pthread.h>

// Dichiarazioni
extern pthread_mutex_t mutexListaClient; 
extern ListaClient* listaClient;


#endif