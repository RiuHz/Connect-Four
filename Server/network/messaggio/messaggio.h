#ifndef MESSAGGIO_H
#define MESSAGGIO_H

#include <stdlib.h>

#include "../shared/protocol.h"

typedef struct Messaggio {
    MessageType tipo;
    uint32_t * payload;
} Messaggio;

Messaggio creaMessaggio(MessageType tipo, uint32_t * payload);

void eliminaMessaggio(Messaggio * messaggio);

#endif
