#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define BOARD_ROWS 6
#define BOARD_COLUMNS 7

// REQ = Request fatte dal client
// RES = Response inviate dal server
// EVT = Event eventi inviati dal server

typedef enum {
    REQ_CONNECT = 1,
    REQ_DISCONNECT,
    REQ_CREATE_GAME,
    REQ_JOIN_GAME,
    REQ_LEAVE_GAME,
    REQ_GAMES_LIST,
    RES_GAMES_LIST,
    EVT_GAMES_LIST_UPDATED,
    EVT_GAME_CREATED,
    EVT_GAME_ENDED,
    REQ_MOVE,
    EVT_GAME_WON,
    EVT_GAME_LOST,
    EVT_GAME_DRAW,
    REQ_REMATCH_ACCEPTED,
    REQ_REMATCH_DENIED,
    RES_REMATCH_ACCEPTED,
    RES_REMATCH_DENIED
} MessageType;

// Ogni messaggio è della struttura [MessageHeader][Message] così anche in TCP sappiamo quanti byte aspettare

typedef struct {
    uint32_t messageType;
    uint32_t length;
} MessageHeader;

typedef struct {
    char playerName[20];
} Payload_REQ_CREATE_GAME;

typedef struct {
    GamesList partite;
} Payload_RES_GAMES_LIST;

typedef struct {
    GamesList listaPartite;
} Payload_EVT_GAMES_LIST_UPDATED;

typedef struct {
    Game partita;
} Payload_EVT_GAME_CREATED;

typedef struct {
    Game partita;
} Payload_EVT_GAME_ENDED;

typedef struct {
    uint32_t column;
} Payload_REQ_MOVE;

typedef enum {
    CREATED = 1,
    WAITING,
    IN_PROGRESS,
    ENDED
} GameState;

typedef struct {
    uint32_t id;
    char proprietario[20];
    char avversario[20];
    GameState stato;
    Game * next = nullptr;
} Game;

typedef struct {
    Game * head = nullptr;
} GamesList;

#endif
