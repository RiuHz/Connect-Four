#ifndef MESSAGGIO_H
#define MESSAGGIO_H

#include "../shared/protocol.h"

typedef struct Messaggio {
    MessageType tipo;
    void * payload;
} Messaggio;

#endif
