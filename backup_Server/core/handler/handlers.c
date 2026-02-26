#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


#include "handlers.h"
#include "../shared/protocol.h"
#include "Request/requests.h"
#include "../global/globals.h"

MessageHeader identificaPacchetto(ClientInfo *clientConnesso){
    MessageHeader pacchetto;
    letturaSicuraDelPacchetto(clientConnesso->socketClient, &pacchetto, sizeof(MessageHeader));
    return pacchetto;
}

/*Leggiamo in modo sicuro il pacchetto e restituiamo la lunghezza dei byte letti */
size_t letturaSicuraDelPacchetto(int socketClientConnesso, void *buffer, size_t lunghezzaDaLeggere){
    size_t bytesLetti = 0;
    char *ptr = (char*)buffer;

    while (bytesLetti < lunghezzaDaLeggere) {
        // Chiediamo di leggere solo quello che manca (lunghezzaDaLeggere - bytesLetti)
        ssize_t byteRimanenti = recv(socketClientConnesso, ptr + bytesLetti, lunghezzaDaLeggere - bytesLetti, 0);
        
        if (byteRimanenti <= 0) return (size_t)byteRimanenti; // Errore o chiusura conn. client
        
        bytesLetti += (size_t)byteRimanenti;
    }
    return bytesLetti; // Ho letto tutto!
}

void processaPacchetto(MessageHeader tipoPackage ,ClientInfo *clientConnesso){

    uint32_t dimensionePayload=0;
    if(tipoPackage.length > 0){
        dimensionePayload=ntohl(tipoPackage.length);
    }
    
    tipoPackage.type=ntohl(tipoPackage.type);

    switch(tipoPackage.type) {
        case REQ_CONNECT:
            richiestaConnessione(clientConnesso,dimensionePayload);
        break;

        case REQ_CREATE_GAME:
            richiestaCreaPartita(clientConnesso);
        break;

        case REQ_GAMES_LIST:
            richiestaListaPartite(clientConnesso);
        break;

        default:
            printf("Pacchetto sconosciuto! Pulisco i dati inutili.\n"); // DEBUG 
            puliziaBuffer(clientConnesso->socketClient, dimensionePayload); 
        break;
        
    }
}

void puliziaBuffer(int socketClientConnesso, uint32_t lunghezzaDaLeggere){
    if (lunghezzaDaLeggere <= 0) return;

    char *bufferTemporaneo = malloc(lunghezzaDaLeggere); 
    if (bufferTemporaneo) {
        letturaSicuraDelPacchetto(socketClientConnesso, bufferTemporaneo, lunghezzaDaLeggere); 
        free(bufferTemporaneo);
    }
    
}

