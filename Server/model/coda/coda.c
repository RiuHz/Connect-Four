#include "coda.h"

MessaggioBroadcast * creaMessaggioBroadcast(Messaggio messaggio) {
    MessaggioBroadcast * messaggioBroadcast = malloc(sizeof(MessaggioBroadcast));

    messaggioBroadcast -> messaggio = malloc(sizeof(Messaggio));
    messaggioBroadcast -> messaggio -> header = messaggio.header;
    
    messaggioBroadcast -> messaggio -> payload = malloc(messaggio.header.length);
    memcpy(messaggioBroadcast -> messaggio -> payload, messaggio.payload, messaggio.header.length);

    return messaggioBroadcast;
}

void cancellaMessaggioBroadcast(MessaggioBroadcast * messaggioBroadcast) {
    free(messaggioBroadcast -> messaggio -> payload);
    free(messaggioBroadcast -> messaggio);

    messaggioBroadcast -> messaggio = NULL;
}

void accodaMessaggioBroadcast(CodaBroadcast * coda, Messaggio messaggio) {
    MessaggioBroadcast * messaggioBroadcast = creaMessaggioBroadcast(messaggio);

    pthread_mutex_lock(& coda -> mutex);

    if (coda -> head == NULL && coda -> tail == NULL) {
        coda -> head = coda -> tail = messaggioBroadcast;
    } else {
        coda -> tail -> next = messaggioBroadcast;
        coda -> tail = messaggioBroadcast;
    }

    pthread_mutex_unlock(& coda -> mutex);
    sem_post(& coda -> semaforo);
}

void stampaCodaBroadcast(CodaBroadcast * coda) {
    MessaggioBroadcast * messaggioBroadcast = coda -> head;

    pthread_mutex_lock(& coda -> mutex);

    if (messaggioBroadcast == NULL) {
        printf("La lista dei Client e' vuota\n");  
    } else {
        printf("Lista client: ");

        while(messaggioBroadcast != NULL) {
            printf("Codice evento: %d\n", messaggioBroadcast -> messaggio -> header.type);
            messaggioBroadcast = messaggioBroadcast -> next;
        }  
    }

    pthread_mutex_unlock(& coda -> mutex);
}

void decodaMessaggioBroadcast(CodaBroadcast * coda) {
    pthread_mutex_lock(& coda -> mutex);

    if (coda -> head == NULL && coda -> tail == NULL) {
        printf("La coda broadcast è vuota...\n");
        exit(1);
    }

    MessaggioBroadcast * messaggio = coda -> head;

    coda -> head = coda -> head -> next;
   
    if (coda -> head == NULL) {
        coda -> tail = NULL;
    }

    cancellaMessaggioBroadcast(messaggio);
    free(messaggio);

    pthread_mutex_unlock(& coda -> mutex);
}
