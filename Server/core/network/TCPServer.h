#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <sys/types.h> // per ssize_T
#include <sys/socket.h> // per sock_addr_in
#include <netinet/in.h> // per sock_addr_in

// Strutture dati necessarie
typedef struct ListaClient {
        int socketClient;
        struct ListaClient *next;
} ListaClient;

// Funzioni per liste
// inserimento in testa - ricerca - cancellazione di un determinato nodo
void aggiungiClient(int nuovoClientConnesso);
void stampaLista();



int creaSocketServerTCP();
void avviaServer(int socketServer);
void associaThreadClient(int nuovoClientConnesso);
void *gestioneClientThread(void *arg);

#endif