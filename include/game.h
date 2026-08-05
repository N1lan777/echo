#pragma once
#include <stdbool.h>
#include <SDL.h>
#include <stdint.h>
#define MAX_BLOCKS 50
#define MAX_SCORES 10
#define SCORES_FILE "scorex.txt"

typedef enum {
    MENU,
    GAME,
    PAUSE,
    RECORD,
    NAME_INPUT,
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
    bool hp;
    SDL_Color color;
} Block;
// player data
typedef struct {
    short score;
    char name[32];
} ScoreEntry;

typedef struct {
    Ball ball;
    Paddle paddle;
    Block blocks[MAX_BLOCKS];
    GameScreen gamescreen;
    short score;
    bool is_running;
    char player_name[32];
} GameState;
// board player 
typedef struct {
    ScoreEntry scores[MAX_SCORES];
    int count_scores;
}Leaderboard;

void game_init(GameState* state, bool is_start);
void game_update(GameState* state, float dt);
void game_handle_input(GameState* state, const Uint8* keys, float dt);
void game_handle_click(GameState* state, int mouse_x, int mouse_y);
void game_loading(Leaderboard* board);
void game_save(Leaderboard* board);
void game_leaderboard(Leaderboard* board, const char * name, short score);
void game_sort(Leaderboard* board); 
void game_text_handle_input(GameState* state, const char* text);