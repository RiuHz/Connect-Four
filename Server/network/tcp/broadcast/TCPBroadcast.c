#include "TCPBroadcast.h"

void avviaBroadcast(Server * server) {

    printf("[Broadcast] [Thread: %lu] Servizio di broadcast avviato correttamente\n", (unsigned long) pthread_self());
    
    while (true) {
        dispatch_semaphore_wait(server -> codaBroadcast -> semaforo, DISPATCH_TIME_FOREVER);
        
        pthread_mutex_lock(& server -> codaBroadcast -> mutex); 
        pthread_mutex_lock(& server -> listaClient -> mutex); 

        while (server -> codaBroadcast -> head != NULL) {
            MessaggioBroadcast * messaggioBroadcast = server -> codaBroadcast -> head;

            printf("[Broadcast] [Thread: %lu] Invio del messaggio (tipo: %d) in broadcast\n", (unsigned long) pthread_self(), messaggioBroadcast -> messaggio -> header.type);

            Client * client = server -> listaClient -> head;
        
            while (client != NULL) {
                inviaMessaggio(client, * (messaggioBroadcast -> messaggio));

                client = client -> next;
            }

            decodaMessaggioBroadcast(server -> codaBroadcast);
        }

        pthread_mutex_unlock(& server -> listaClient -> mutex);
        pthread_mutex_unlock(& server -> codaBroadcast -> mutex);
    }

}
