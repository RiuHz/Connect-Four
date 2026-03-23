#ifndef PARTITA_CONTROLLER_H
#define PARTITA_CONTROLLER_H

#include <stdbool.h>

#include "../../../model/client/client.h"
#include "../../../model/server/server.h"

#include "../../../network/tcp/server/TCPServer.h"

void gestisciPartita(Partita * partita);
void inviaAggiornamentoBoard(Partita * partita);

EsitoPartita controllaEsitoProprietario(Partita * partita);
EsitoPartita controllaEsitoAvversario(Partita * partita);

void gestisciLobby(Server * server, Partita * partita);

void gestisciRichiestaPartecipazione(Server * server, Partita * partita, Client * client);


#endif
