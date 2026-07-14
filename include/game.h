#pragma once
#include <stdbool.h>
#include <SDL.h>
#define MAX_BLOCKS 50

typedef enum {
    MENU,
    GAME,
    PAUSE,
    HELP,
    PLAYERS,
    RECORD,
    EXIT,
} GameScreen;

typedef struct {
    float x;
    float y;
    float vx;
    float vy;
} Ball;

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Paddle;

typedef struct {
    float x;
    float y;
    float width;
    float height;
    short hp;
} Block;

typedef struct {
    Ball ball;
    Paddle paddle;
    bool is_running;
    short score;
    Block blocks[MAX_BLOCKS];
    bool won;
    GameScreen gamescreen;
} GameState;

void game_init (GameState* state);
void game_update (GameState* state, float dt);
void game_handle_input(GameState* state, const Uint8* keys, float dt);

