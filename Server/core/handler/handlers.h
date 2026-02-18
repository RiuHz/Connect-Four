#ifndef HANDLERS_H
#define HANDLERS_H

#include "../global/globals.h" 

MessageHeader identificaPacchetto(ClientInfo *clientConnesso);
void processaPacchetto(MessageHeader tipoPackage ,ClientInfo *clientConnesso);
size_t letturaSicuraDelPacchetto(int socketClientConnesso, void *buffer, size_t lunghezzaDaLeggere);
void puliziaBuffer(int socketClientConnesso, uint32_t lunghezzaDaLeggere);

#endif