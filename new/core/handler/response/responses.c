#include "responses.h"


Messaggio rispostaConnessione(){
    Messaggio messaggioRisposta;

    messaggioRisposta.tipo=RES_CONNECT_ACCEPTED;
    messaggioRisposta.payload=NULL;

    return messaggioRisposta;
    
}


Messaggio rispostaListaPartite(ListaPartite * lista){
    // Invio il pacchetto di tutto ok
    Messaggio messagioRisposta;
    messagioRisposta.tipo=RES_GAMES_LIST;
    
    // 1) messagioRisposta.payload= associare il puntatore allo stream di byte

    // 2) ((Payload_RES_GAMES_LIST *)messagioRisposta.payload)->games associare il vettore di partite o lo stream di byte

    // ((Payload_RES_GAMES_LIST *)messagioRisposta.payload)->numberOfGames=htonl(numeroGiochi) 
    
}



// ListaPartite -> Game 1 -> Game2 -> Game3...

// Header tipo = ListaPartite, length = (sizeof(Game) * sizeof(uint32_t))
// payload -> [ByteGame1][ByteGame2][ByteGame3]
