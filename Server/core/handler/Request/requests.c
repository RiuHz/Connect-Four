#include "requests.h"
#include "../../shared/protocol.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

void richiestaListaPartite(int socketClientConnesso){

    // BOZZA DI PROVA
    Game p1;
    p1.id=1;
    strcpy(p1.proprietario,"Mario");
    strcpy(p1.proprietario,"");
    p1.stato=1u;

    Payload_RES_GAMES_LIST lista;
    lista.games[0]=p1;
    lista.numberOfGames=1;

    MessageHeader messageHeader;
    messageHeader.messageType=RES_GAMES_LIST;
    messageHeader.length=sizeof(Game); // per un solo game altrimenti numero partite * sizeofGame

    send(socketClientConnesso, &messageHeader, sizeof(messageHeader), 0);
    
    send(socketClientConnesso, &lista, sizeof(Game), 0); // il 3° parametro va cambiato con dimensione totale = numeroPartite * sizeoOfGame


    // recupero la lista di partite
   
    // conversione da lista a vettore per mandarlo?

    //invio la lista di partite al client


}