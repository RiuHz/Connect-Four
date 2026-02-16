#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>

#include "handlers.h"
#include "../shared/protocol.h"
#include "Request/requests.h"

uint32_t identificaPacchetto(int socketClientConnesso){
    uint32_t packageTipo;
    letturaSicuraDelPacchetto(socketClientConnesso, &packageTipo, sizeof(uint32_t));
    return packageTipo;
}

/*Leggiamo in modo sicuro il pacchetto e restituiamo la lunghezza dei byte letti, se <=0 allora c'è stato un errore / disconnessione */
ssize_t letturaSicuraDelPacchetto(int socketClientConnesso, void *buffer, size_t lunghezzaDaLeggere){
    size_t bytesLetti = 0;
    char *ptr = (char*)buffer;

    while (bytesLetti < lunghezzaDaLeggere) {
        // Chiediamo di leggere solo quello che manca (lunghezzaDaLeggere - bytesLetti)
        ssize_t byteRimanenti = recv(socketClientConnesso, ptr + bytesLetti, lunghezzaDaLeggere - bytesLetti, 0);
        
        if (byteRimanenti <= 0) return byteRimanenti; // Errore o chiusura
        
        bytesLetti += (size_t)byteRimanenti;
    }
    return (ssize_t)bytesLetti; // Ho letto tutto!
}

void processaPacchetto(uint32_t tipoPackage ,int socketClientConnesso){
    switch(tipoPackage) {

        case REQ_GAMES_LIST:
            richiestaListaPartite(socketClientConnesso);
        break;
        
}
}