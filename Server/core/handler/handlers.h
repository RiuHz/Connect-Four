#ifndef HANDLERS_H
#define HANDLERS_H

uint32_t identificaPacchetto(int socketClientConnesso);
void processaPacchetto(uint32_t tipoPackage ,int socketClientConnesso);
size_t letturaSicuraDelPacchetto(int socketClientConnesso, void *buffer, size_t lunghezzaDaLeggere);

#endif