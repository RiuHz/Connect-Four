#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>

#include <string.h>
#include <sys/socket.h>

#include "../handler/handlers.h"

#include "../../data/client/client.h"

void associaThreadConnessione(int socket);

void gestioneConnessioneThread(Client * client);

#endif
