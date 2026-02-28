#ifndef BROADCAST_THREAD_H
#define BROADCAST_THREAD_H

#include "../../../model/server/server.h"

#include "../../../network/tcp/broadcast/TCPBroadcast.h"

void avviaThreadBroadcast(Server * server);

void * wrapperBroadcast(void * arg);

#endif
