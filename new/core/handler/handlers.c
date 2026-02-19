#include "handlers.h"

Messaggio attendiMessaggio(Client * client, MessageType messaggioAtteso) {
    MessageHeader header;
    uint32_t * buffer;

    do {

        leggiFlussoDati(client, &header, sizeof(header));

        header.type = ntohl(header.type);
        header.length = ntohl(header.length);

        if (header.length <= 0)
            continue;

        buffer = malloc(sizeof(header.length));
        leggiFlussoDati(client, &buffer, sizeof(header.length));

    } while (header.type != messaggioAtteso);

    return processaMessaggio(header, buffer);
}

Messaggio processaMessaggio(MessageHeader header, uint32_t * payload) {

    uint32_t dimensione = header.length;

    switch (header.type) {
        case REQ_CONNECT:
            return richiestaConnessione(payload);
        break;

        case REQ_DISCONNECT:
            return richiestaDisconnessione();
        break;

        case REQ_CREATE_GAME:
            return richiestaCreaPartita();
        break;

        case REQ_JOIN_GAME:
            return richiestaPartecipaPartita(payload);
        break;
        
        case REQ_LEAVE_GAME:
            return richiestaLasciaPartita();
        break;
        
        case REQ_GAME_ACCEPTED:
            return richiestaAccettaPartita();
        break;
        
        case REQ_GAME_DENIED:
            return richiestaLasciaPartita();
        break;

        case REQ_GAMES_LIST:
            return richiestaListaPartite();
        break;

        case REQ_MOVE:
            return richiestaMossa(payload);
        break;

        case REQ_REMATCH_ACCEPTED:
            return richiestaAccettaRivincita();
        break;

        case REQ_REMATCH_DENIED:
            return richiestaRifiutaRivincita();
        break;
    }
}

void leggiFlussoDati(Client * client, void * buffer, size_t lunghezza) {
    ssize_t bytesLetti = 0;
    char * ptr = (char *) buffer;

    while (bytesLetti < lunghezza) {
        ssize_t byteRimanenti = recv(client -> socket, ptr + bytesLetti, lunghezza - bytesLetti, 0);
        
        if (byteRimanenti <= 0) {
            fprintf(stderr, "Impossibile leggere dal buffer TCP del thread %d (%s)", pthread_self, client -> nome);
            exit(1);
        }
        
        bytesLetti += byteRimanenti;
    }
}
