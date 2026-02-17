#ifndef THREADS_H
#define THREADS_H

void associaThreadClient(int nuovoClientConnesso);
void *gestioneClientThread(void *arg);

#endif