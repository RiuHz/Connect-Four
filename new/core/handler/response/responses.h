#ifndef RESPONSES_H
#define RESPONSES_H

#include "../../data/list/list.h"
#include "../../shared/protocol.h"
#include "../../threading/threads.h"
#include "../handlers.h"
#include "../../network/TCPServer.h"


Messaggio rispostaConnessione();
Messaggio rispostaListaPartite(ListaPartite * lista);

#endif
