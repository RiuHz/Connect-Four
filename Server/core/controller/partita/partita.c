#include "partita.h"

void gestisciPartita(Partita * partita) {
    bool rematch = true;
    bool partitaInCorso = true;

    bool turnoProprietario = true;
    bool turnoAvversario = false;

    printf("[Partita] [Thread: %lu] La Partita (%d) è iniziata\n", (unsigned long) pthread_self(), partita -> id);

    while (rematch) {

        while (partitaInCorso) {

            while (turnoProprietario) {
                Messaggio messaggio = attendiMessaggio(partita -> proprietario);

                switch (messaggio.header.type) {
                    case REQ_MOVE: {
                        unsigned int mossa = richiestaMossa(messaggio.payload);

                        Messaggio risposta;

                        if (!controllaValiditaMossa(partita, mossa)) {
                            risposta = rispostaMossa(false);
                        } else {
                            risposta = rispostaMossa(true);

                            aggiungiMossaProprietario(partita, mossa);

                            turnoProprietario = false;
                            turnoAvversario = true;
                        }

                        inviaMessaggio(partita -> proprietario, risposta);

                        eliminaMessaggio(& risposta);
                    }
                    break;

                    default:
                        eliminaMessaggio(& messaggio);
                }
            }

            inviaAggiornamentoBoard(partita);

            if (controllaEsitoProprietario(partita) != NON_TERMINATA) {
                partitaInCorso = false;
                break;
            }

            while (turnoAvversario) {
                Messaggio messaggio = attendiMessaggio(partita -> avversario);

                switch (messaggio.header.type) {
                    case REQ_MOVE: {
                        unsigned int mossa = richiestaMossa(messaggio.payload);

                        Messaggio risposta;

                        if (!controllaValiditaMossa(partita, mossa)) {
                            risposta = rispostaMossa(false);
                        } else {
                            risposta = rispostaMossa(true);

                            aggiungiMossaAvversario(partita, mossa);

                            turnoProprietario = true;
                            turnoAvversario = false;
                        }

                        inviaMessaggio(partita -> avversario, risposta);

                        eliminaMessaggio(& risposta);
                    }
                    break;

                    default:
                        eliminaMessaggio(& messaggio);
                }
            }

            inviaAggiornamentoBoard(partita);

            if (controllaEsitoAvversario(partita) != NON_TERMINATA) {
                partitaInCorso = false;
            }

        }

        Messaggio richiestaProprietario = attendiMessaggio(partita -> proprietario);
        Messaggio richiestaAvversario = attendiMessaggio(partita -> avversario);

        bool rematchProprietario = richiestaRivincita(richiestaProprietario.payload);
        bool rematchAvversario = richiestaRivincita(richiestaAvversario.payload);

        eliminaMessaggio(& richiestaProprietario);
        eliminaMessaggio(& richiestaAvversario);

        Messaggio risposta;

        if (rematchProprietario == true && rematchAvversario == true) {
            risposta = rispostaRivincita(true);
        } else {
            risposta = rispostaRivincita(false);

            rematch = false;
        }

        inviaMessaggio(partita -> proprietario, risposta);
        inviaMessaggio(partita -> avversario, risposta);

        eliminaMessaggio(& risposta);
    }

    printf("[Partita] [Thread: %lu] La Partita (%d) è terminata, chiusura del thread...\n", (unsigned long) pthread_self(), partita -> id);

    pthread_exit(NULL);
}

void inviaAggiornamentoBoard(Partita * partita) {
    Messaggio evento = eventoAggiornamentoBoard(partita);

    inviaMessaggio(partita -> proprietario, evento);
    inviaMessaggio(partita -> avversario, evento);

    eliminaMessaggio(& evento);
}

EsitoPartita controllaEsitoProprietario(Partita * partita) {
    EsitoPartita esito = controllaEsitoPartita(partita, CELLA_PROPRIETARIO);

    switch (esito) {
        case VITTORIA: {
            Messaggio eventoVittoria = creaMessaggio(EVT_GAME_WON, 0, NULL);
            Messaggio eventoSconfitta = creaMessaggio(EVT_GAME_LOST, 0, NULL);

            inviaMessaggio(partita -> proprietario, eventoVittoria);
            inviaMessaggio(partita -> avversario, eventoSconfitta);

            eliminaMessaggio(& eventoVittoria);
            eliminaMessaggio(& eventoSconfitta);
        }
        break;

        case PAREGGIO: {
            Messaggio eventoPareggio = creaMessaggio(EVT_GAME_DRAW, 0, NULL);

            inviaMessaggio(partita -> proprietario, eventoPareggio);
            inviaMessaggio(partita -> avversario, eventoPareggio);

            eliminaMessaggio(& eventoPareggio);
        }
        break;

        case NON_TERMINATA: {
            Messaggio eventoProssimoTurno = creaMessaggio(EVT_NEXT_TURN, 0, NULL);

            inviaMessaggio(partita -> avversario, eventoProssimoTurno);

            eliminaMessaggio(& eventoProssimoTurno);
        }
        break;

        default:
        break;
    }

    return esito;
}

EsitoPartita controllaEsitoAvversario(Partita * partita) {
    EsitoPartita esito = controllaEsitoPartita(partita, CELLA_AVVERSARIO);

    switch (esito) {
        case VITTORIA: {
            Messaggio eventoVittoria = creaMessaggio(EVT_GAME_WON, 0, NULL);
            Messaggio eventoSconfitta = creaMessaggio(EVT_GAME_LOST, 0, NULL);

            inviaMessaggio(partita -> avversario, eventoVittoria);
            inviaMessaggio(partita -> proprietario, eventoSconfitta);

            eliminaMessaggio(& eventoVittoria);
            eliminaMessaggio(& eventoSconfitta);
        }
        break;

        case PAREGGIO: {
            Messaggio eventoPareggio = creaMessaggio(EVT_GAME_DRAW, 0, NULL);

            inviaMessaggio(partita -> proprietario, eventoPareggio);
            inviaMessaggio(partita -> avversario, eventoPareggio);

            eliminaMessaggio(& eventoPareggio);
        }
        break;

        case NON_TERMINATA: {
            Messaggio eventoProssimoTurno = creaMessaggio(EVT_NEXT_TURN, 0, NULL);

            inviaMessaggio(partita -> proprietario, eventoProssimoTurno);

            eliminaMessaggio(& eventoProssimoTurno);
        }
        break;

        default:
        break;
    }

    return esito;
}

void gestisciLobby(Server * server, Partita * partita) {
    bool inLobby = true;

    while (inLobby) {
        Messaggio messaggio = attendiMessaggio(partita -> proprietario);

        switch (messaggio.header.type) {
            case REQ_LEAVE_GAME: {
                inLobby = false;
                printf("[Client] [Thread: %lu] Il proprietario (%s) ha abbandonato la partita (%d)...\n", (unsigned long) pthread_self(), partita -> proprietario -> nome, partita -> id);

                eliminaMessaggio(& messaggio);
            }
            break;

            case REQ_JOIN_DECISION: {
                bool risposta = richiestaRispostaAccessoPartita(messaggio.payload);

                setRisposta(partita, risposta);
                pthread_cond_signal(& partita -> richiesta);

                if (risposta == true) {
                    avviaThreadPartita(partita);

                    attendiTerminePartita(partita);

                    inLobby = false;
                }

                eliminaMessaggio(& messaggio);
            }
            break;

            default:
                eliminaMessaggio(& messaggio);
        }
    }

    Messaggio evento = eventoPartitaTerminata(partita -> id);
    accodaMessaggioBroadcast(server -> codaBroadcast, evento);

    eliminaMessaggio(& evento);

    printf("[Client] [Thread: %lu] Rimossa la Partita creata da %s\n", (unsigned long) pthread_self(), partita -> proprietario -> nome);

    rimuoviPartita(server -> listaPartite, partita);
}

void gestisciRichiestaPartecipazione(Server * server, Partita * partita, Client * client) {
    aggiungiAvversario(partita, client);

    Messaggio evento = eventoAggiornamentoPartita(partita);
    accodaMessaggioBroadcast(server -> codaBroadcast, evento);

    eliminaMessaggio(& evento);

    pthread_mutex_lock(& partita -> mutex);

    Messaggio richiesta = eventoRichiestaPartecipazione(partita -> avversario);
    inviaMessaggio(partita -> proprietario, richiesta);

    eliminaMessaggio(& richiesta);

    pthread_cond_wait(& partita -> richiesta, & partita -> mutex);

    Messaggio risposta = rispostaAccessoPartita(partita -> risposta);

    inviaMessaggio(partita -> avversario, risposta);

    eliminaMessaggio(& risposta);

    if (partita -> risposta == true) {
        pthread_mutex_unlock(& partita -> mutex);

        attendiTerminePartita(partita);
    } else {
        partita -> avversario = NULL;

        pthread_mutex_unlock(& partita -> mutex);

        Messaggio evento = eventoAggiornamentoPartita(partita);
        accodaMessaggioBroadcast(server -> codaBroadcast, evento);

        eliminaMessaggio(& evento);
    }
}
