#include "requests.h"
#include "../../shared/protocol.h"
#include "../../threading/threads.h"
#include "../handlers.h"
#include "../../network/TCPServer.h"
#include "../Response/responses.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

void richiestaConnessione(ClientInfo *clientConnesso,uint32_t dimensionePayloadDaLeggere){
    // Dichiaro la struttura che mi serve
    Payload_REQ_CONNECT payloadRichiestaConnessione;

    // Controllo di sicurezza
    if (dimensionePayloadDaLeggere != sizeof(Payload_REQ_CONNECT)) {
        puliziaBuffer(clientConnesso->socketClient, dimensionePayloadDaLeggere);  // devo comunque leggere la dimensione dichiarata
        return; // gestire poi la logica per farlo sapere al client che l'operazione non è andata a buon fine (con una send probabilmente)
    }

    // Leggo i dati
    if (letturaSicuraDelPacchetto(clientConnesso->socketClient, &payloadRichiestaConnessione, sizeof(Payload_REQ_CONNECT)) <= 0) {
        return; // Errore di rete
    }

    // Logica
    strncpy(clientConnesso->nomeClient, payloadRichiestaConnessione.playerName, 20);

    // avviso il client che è tutto ok
    rispostaConnessione(clientConnesso);
}

void richiestaCreaPartita(ClientInfo *clientConnesso){
    // crea partita
    Partita partita;
    partita.id=ottieniNuovoIdentificativoPartita();
    strncpy(partita.proprietario, clientConnesso->nomeClient, 20);
    partita.socketProprietario=clientConnesso->socketClient;
    partita.stato=1;

    // aggiungi alla lista partite
    aggiungiPartitaAllaLista(partita);

    // avvisa gli altri client che è stata creata una nuova partita
    inviaBroadcast(&partita,sizeof(Partita));   

    rispostaCreaPartita(clientConnesso);

}

void richiestaListaPartite(ClientInfo *clientConnesso){

    // recupero la lista di partite e conversione in struct di partite

    size_t dimensionePacchetto = 0;
    Payload_RES_GAMES_LIST *listaPartiteOttenute = ottieniListaPartite(&dimensionePacchetto);

    // invio la lista di partite al client

    rispostaListaPartite(clientConnesso,dimensionePacchetto,listaPartiteOttenute);

    free(listaPartiteOttenute); 

}

