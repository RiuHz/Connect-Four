#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdint.h>
#include <unistd.h>

uint32_t identificaPacchetto(int socketClientConnesso);
void processaPacchetto(uint32_t tipoPackage ,int socketClientConnesso);
ssize_t letturaSicuraDelPacchetto(int socketClientConnesso, void *buffer, size_t lunghezzaDaLeggere);


#endif