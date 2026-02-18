#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define NAME_LEN 21

#define BOARD_ROWS 6
#define BOARD_COLUMNS 7

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 1946

typedef enum {
    GAME_CREATED = 1,
    GAME_WAITING,
    GAME_IN_PROGRESS,
    GAME_ENDED
} GameState;

typedef struct {
    uint32_t id;
    char proprietario[NAME_LEN];
    char avversario[NAME_LEN];
    uint32_t stato;
} Game;

// (REQ = Request) Richieste effettuate dal client
// (RES = Response) Riposte inviate dal server
// (EVT = Event) Eventi inviati dal server

typedef enum {
    REQ_CONNECT = 1,
    RES_CONNECT_ACCEPTED,
    REQ_DISCONNECT,
    REQ_CREATE_GAME,
    RES_CREATE_GAME_ACCEPTED,
    REQ_JOIN_GAME,
    REQ_LEAVE_GAME,
    EVT_OPPONENT_JOIN,
    REQ_GAME_ACCEPTED,
    REQ_GAME_DENIED,
    EVT_GAME_ACCEPTED,
    EVT_GAME_DENIED,
    REQ_GAMES_LIST,
    RES_GAMES_LIST,
    EVT_GAMES_LIST_UPDATED,
    EVT_GAME_CREATED,
    EVT_GAME_ENDED,
    REQ_MOVE,
    EVT_OPPONENT_MOVE,
    EVT_GAME_WON,
    EVT_GAME_LOST,
    EVT_GAME_DRAW,
    REQ_REMATCH_ACCEPTED,
    REQ_REMATCH_DENIED,
    EVT_REMATCH_ACCEPTED,
    EVT_REMATCH_DENIED
} MessageType;

// Ogni messaggio è della struttura [MessageHeader][Message] così anche in TCP sappiamo quanti byte aspettare

typedef struct {
    uint32_t type;
    uint32_t length;
} MessageHeader;

typedef struct {
    char playerName[NAME_LEN];
} Payload_REQ_CONNECT;

typedef struct {
    uint32_t numberOfGames;
    Game games[];
} Payload_RES_GAMES_LIST;

typedef struct {
    uint32_t numberOfGames;
    Game games[];
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

typedef struct {
    uint32_t column;
} Payload_EVT_OPPONENT_MOVE;

#endif
