#ifndef MESSAGGIO_H
#define MESSAGGIO_H

#include <stdlib.h>

#include "../../network/shared/protocol.h"

typedef struct Messaggio {
    MessageHeader header;
    uint32_t * payload;
} Messaggio;

Messaggio creaMessaggio(MessageType tipo, uint32_t dimensione, uint32_t * payload);

void eliminaMessaggio(Messaggio * messaggio);

#endif
