#ifndef THREADS_H
#define THREADS_H

void associaThreadClient(int nuovoClientConnesso);
void *gestioneClientThread(void *arg);
void inviaBroadcast(char* msg);

#endif