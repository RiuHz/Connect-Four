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
    messagioRisposta.payload=malloc(sizeof(Payload_RES_GAMES_LIST) / sizeof(unsigned int));
    ((Payload_RES_GAMES_LIST *)messagioRisposta.payload)->games=malloc(sizeof(Game) * lista->contatore);

    /* La struttur del messaggio si compone come header, lunghezza ? usint 32_t e payload che sono i dati della struct
    sarà il client che interpreta il payload sulla base della struct*/

    for(int i=0;i<lista->contatore;i++){
        ((Payload_RES_GAMES_LIST *)messagioRisposta.payload)->games[i]=malloc(sizeof(Game));
        
        (Payload_RES_GAMES_LIST *)messagioRisposta.payload[i]
    }
    


    
    // 1) messagioRisposta.payload= associare il puntatore allo stream di byte

    // 2) ((Payload_RES_GAMES_LIST *)messagioRisposta.payload)->games associare il vettore di partite o lo stream di byte

    // ((Payload_RES_GAMES_LIST *)messagioRisposta.payload)->numberOfGames=htonl(numeroGiochi) 
    
}



// ListaPartite -> Game 1 -> Game2 -> Game3...

// Header tipo = ListaPartite, length = (sizeof(Game) * sizeof(uint32_t))
// payload -> [ByteGame1][ByteGame2][ByteGame3]
