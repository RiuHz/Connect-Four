
#ifndef THREADS_H
#define THREADS_H

#include "../global/globals.h"

void associaThreadClient(int nuovoClientConnesso);
void *gestioneClientThread(void *arg);

#endif