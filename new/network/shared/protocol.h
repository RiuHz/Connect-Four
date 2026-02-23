#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define NAME_LEN 20

#define BOARD_ROWS 6
#define BOARD_COLUMNS 7

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 1926

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

typedef struct {
    uint32_t rows[BOARD_ROWS];
    uint32_t columns[BOARD_COLUMNS];
} Board;

// (REQ = Request) Richieste effettuate dal client
// (RES = Response) Riposte inviate dal server
// (EVT = Event) Eventi inviati dal server

typedef enum {
    REQ_CONNECT = 1, // Payload = char nome[NAME_LEN]

    REQ_DISCONNECT,

    REQ_CREATE_GAME,
    RES_CREATE_GAME, // Payload = Game
    
    REQ_JOIN_GAME,
    EVT_OPPONENT_JOIN_GAME,
    REQ_RESPOND_OPPONENT_JOIN_GAME, // Payload = Boolean
    RES_JOIN_GAME, // Payload = Boolean
    
    REQ_LEAVE_GAME,
    
    REQ_GAMES_LIST,
    RES_GAMES_LIST, // Payload = Game List
    
    EVT_GAMES_LIST_UPDATED, // Payload = Game List
    EVT_GAME_CREATED, // Payload = Game List
    EVT_GAME_ENDED, // Payload = Game List
    
    REQ_MOVE,
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
