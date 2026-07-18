#pragma once

#include <stdbool.h>
#include <SDL.h>
#include "vars.h"

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
    float r;
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
    char name[20];
    short score;
} ScoreEntry;

typedef struct {
    Ball ball;
    Paddle paddle;
    bool is_running;
    short score;
    Block blocks[MAX_BLOCKS];
    bool won;
    GameScreen gamescreen;
} GameState;

typedef struct {
    ScoreEntry scores[MAX_SCORES];
    int count_scores;
} Leaderboard;

void game_init (GameState* state);
void game_update (GameState* state, float dt);
void game_handle_input(GameState* state, const Uint8* keys, float dt);
void game_handle_click(GameState* state, int mouse_x, int mouse_y);
void game_loading(Leaderboard* board);
void game_save(Leaderboard* board);
