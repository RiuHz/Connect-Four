#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>


#include "handlers.h"
#include "../shared/protocol.h"
#include "Request/requests.h"
#include "../global/globals.h"

uint32_t identificaPacchetto(int socketClientConnesso){
    uint32_t packageTipo;
    letturaSicuraDelPacchetto(socketClientConnesso, &packageTipo, sizeof(uint32_t));
    return packageTipo;
}

/*Leggiamo in modo sicuro il pacchetto e restituiamo la lunghezza dei byte letti, se <=0 allora c'è stato un errore / disconnessione */
size_t letturaSicuraDelPacchetto(int socketClientConnesso, void *buffer, size_t lunghezzaDaLeggere){
    size_t bytesLetti = 0;
    char *ptr = (char*)buffer;

    while (bytesLetti < lunghezzaDaLeggere) {
        // Chiediamo di leggere solo quello che manca (lunghezzaDaLeggere - bytesLetti)
        ssize_t byteRimanenti = recv(socketClientConnesso, ptr + bytesLetti, lunghezzaDaLeggere - bytesLetti, 0);
        
        if (byteRimanenti <= 0) return (size_t)byteRimanenti; // Errore o chiusura
        
        bytesLetti += (size_t)byteRimanenti;
    }
    return bytesLetti; // Ho letto tutto!
}

void processaPacchetto(uint32_t tipoPackage ,int socketClientConnesso){
    switch(tipoPackage) {

        case REQ_GAMES_LIST:
            richiestaListaPartite(socketClientConnesso);
        break;
        case REQ_CREATE_GAME:
            richiestaCreaPartita(socketClientConnesso);
        break;
        
    }
}

