#include "responses.h"
#include "../../shared/protocol.h"
#include "../../threading/threads.h"
#include "../handlers.h"
#include "../../network/TCPServer.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

void rispostaConnessione(ClientInfo *clientConnesso){
    // Invio il pacchetto di tutto ok
    MessageHeader messagioRisposta;
    messagioRisposta.type=RES_CONNECT_ACCEPTED;
    messagioRisposta.length = htonl(0);

    if ( send(clientConnesso->socketClient, &messagioRisposta, sizeof(MessageHeader), 0) ){ // DEBUG
        perror("Errore invio header pacchetto di risposta alla connessione accettata");
        return;
    }

}

void rispostaCreaPartita(ClientInfo *clientConnesso){
     // Invio il pacchetto di tutto ok
    MessageHeader messagioRisposta;
    messagioRisposta.type=RES_CREATE_GAME_ACCEPTED;
    messagioRisposta.length = htonl(0);

    if (send(clientConnesso->socketClient, &messagioRisposta, sizeof(MessageHeader), 0) < 0) { // DEBUG, lasciare solo la chiamata
        perror("Errore invio header pacchetto di risposta alla creazione accettata della partita");
        return;
    }
    
}

void rispostaListaPartite(ClientInfo *clientConnesso, size_t dimensioneDaInviare, Payload_RES_GAMES_LIST *listaPartiteDaInviare ){

    // Invio il pacchetto di tutto ok
    MessageHeader messagioRisposta;
    messagioRisposta.type=RES_GAMES_LIST;
    messagioRisposta.length = htonl((uint32_t)dimensioneDaInviare);

    if (send(clientConnesso->socketClient, &messagioRisposta, sizeof(MessageHeader), 0) < 0) { // DEBUG
        perror("Errore invio header pacchetto di risposta lista di partite");
        return;
    }

    if (send(clientConnesso->socketClient, listaPartiteDaInviare, dimensioneDaInviare, 0) < 0) { // DEBUG
        perror("Errore invio payload pacchetto di risposta lista di partite");
    }
    
}



// ListaPartite -> Game 1 -> Game2 -> Game3...

// Header tipo = ListaPartite, length = (sizeof(Game) * sizeof(uint32_t))
// payload -> [ByteGame1][ByteGame2][ByteGame3]
