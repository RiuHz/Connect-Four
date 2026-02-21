#include "events.h"


Messaggio eventoPartitaCreata(Game partitaCreata){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_GAME_CREATED;
    messagioRisposta.payload = malloc(sizeof(Payload_EVT_GAME_CREATED));

    ((Payload_EVT_GAME_CREATED *)messagioRisposta.payload)->partita.id=htonl(partitaCreata.id);
    strcpy(((Payload_EVT_GAME_CREATED *) messagioRisposta.payload) -> partita.proprietario, partitaCreata.proprietario);
    strcpy(((Payload_EVT_GAME_CREATED *) messagioRisposta.payload) -> partita.avversario, partitaCreata.avversario);
    ((Payload_EVT_GAME_CREATED *)messagioRisposta.payload)->partita.stato=htonl(partitaCreata.stato);

    return messagioRisposta;
}

Messaggio eventoPartitaAccettata(){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_GAME_ACCEPTED;
    messagioRisposta.payload=NULL;

    return messagioRisposta;
}

Messaggio eventoPartitaRifiutata(){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_GAME_DENIED;
    messagioRisposta.payload=NULL;

    return messagioRisposta;
}

Messaggio eventoPartitaTerminata(Game partitaTerminata){
   Messaggio messagioRisposta;

   messagioRisposta.tipo=EVT_GAME_ENDED;
   messagioRisposta.payload = malloc(sizeof(Payload_EVT_GAME_ENDED));

   ((Payload_EVT_GAME_ENDED *)messagioRisposta.payload)->partita.id=htonl(partitaTerminata.id);
    strcpy(((Payload_EVT_GAME_ENDED *) messagioRisposta.payload) -> partita.proprietario, partitaTerminata.proprietario);
    strcpy(((Payload_EVT_GAME_ENDED *) messagioRisposta.payload) -> partita.avversario, partitaTerminata.avversario);
   ((Payload_EVT_GAME_ENDED *)messagioRisposta.payload)->partita.stato=htonl(partitaTerminata.stato);

   return messagioRisposta;
}

Messaggio eventoMossaAvversario(uint32_t mossaAvversario){
   Messaggio messagioRisposta;

   messagioRisposta.tipo=EVT_OPPONENT_MOVE;
   messagioRisposta.payload = malloc(sizeof(Payload_EVT_OPPONENT_MOVE));

   ((Payload_EVT_OPPONENT_MOVE *)messagioRisposta.payload) ->column =htonl(mossaAvversario);

   return messagioRisposta;
}

Messaggio eventoPartitaVinta(){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_GAME_WON;
    messagioRisposta.payload=NULL;

    return messagioRisposta;
}

Messaggio eventoPartitaPersa(){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_GAME_LOST;
    messagioRisposta.payload=NULL;

    return messagioRisposta;
}

Messaggio eventoPartitaPareggio(){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_GAME_DRAW;
    messagioRisposta.payload=NULL;

    return messagioRisposta;
}

Messaggio eventoRivincitaAccettata(){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_REMATCH_ACCEPTED;
    messagioRisposta.payload=NULL;

    return messagioRisposta;
}

Messaggio eventoRivincitaRifiutata(){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_REMATCH_DENIED;
    messagioRisposta.payload=NULL;

    return messagioRisposta;
}

Messaggio eventoAggiornamentoListaPartite(Game partitaDaAggiornare){
    Messaggio messagioRisposta;

    messagioRisposta.tipo=EVT_GAMES_LIST_UPDATED;
    messagioRisposta.payload = malloc(sizeof(Payload_EVT_GAMES_LIST_UPDATED));

    ((Payload_EVT_GAMES_LIST_UPDATED *)messagioRisposta.payload)->partita.stato=htonl(partitaDaAggiornare.stato);

    return messagioRisposta;

}