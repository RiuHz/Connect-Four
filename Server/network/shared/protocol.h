#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define NAME_LEN 20

#define BOARD_ROWS 6
#define BOARD_COLUMNS 7

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 1926

typedef enum {
    GAME_WAITING = 1,
    GAME_IN_PROGRESS
} GameState;

typedef struct {
    uint32_t id;
    char proprietario[NAME_LEN];
    char avversario[NAME_LEN];
    uint32_t stato;
} Game;

typedef struct {
    uint32_t grid[BOARD_ROWS][BOARD_COLUMNS];
} Board;

// (REQ = Request) Richieste effettuate dal client
// (RES = Response) Riposte inviate dal server
// (EVT = Event) Eventi inviati dal server

typedef enum {
    // ==== Connessione ====
    REQ_CONNECT = 1, // Payload = char nome[NAME_LEN]
    REQ_DISCONNECT,

    // ==== Creazione Partita ====
    REQ_CREATE_GAME,
    RES_CREATE_GAME, // Payload = Game
    
    // ==== Ingresso Partita ====
    REQ_JOIN_GAME, // Payload = Unsigned int
    EVT_JOIN_REQUEST,
    REQ_JOIN_DECISION, // Payload = Boolean
    RES_JOIN_GAME, // Payload = Boolean
    
    REQ_LEAVE_GAME,
    
    // ==== Lista Partite ====
    REQ_GAMES_LIST,
    RES_GAMES_LIST, // Payload = Game List
    
    EVT_GAME_UPDATE, // Payload = Game
    EVT_GAME_CREATED, // Payload = Game
    EVT_GAME_ENDED, // Payload = Game id
    
    // ==== Svolgimento Partita ====
    REQ_MOVE, // Payload = Unsigned int
    RES_BAD_MOVE,

    EVT_UPDATE_BOARD, // Payload = Board
    EVT_NEXT_TURN,
    EVT_GAME_WON,
    EVT_GAME_LOST,
    EVT_GAME_DRAW,
    
    REQ_REMATCH, // Payload = Boolean
    RES_REMATCH // Payload = Boolean
} MessageType;

// Ogni messaggio è della struttura [MessageHeader][Message] così anche in TCP sappiamo quanti byte aspettare

typedef struct {
    uint32_t type;
    uint32_t length;
} MessageHeader;

#endif
