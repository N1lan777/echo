#pragma once
#include <stdbool.h>

#define MAX_BLOCKS 50

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
} GameState;

void game_init (GameState* state);
void game_update (GameState* state, float dt);


