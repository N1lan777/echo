#include <SDL2/SDL.h>
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


void game_init(GameState* state, bool is_start)
{
    if (is_start) {
        state->score = 0;
        state->is_running = true;
        state->gamescreen = NAME_INPUT; 
    }
    state->player_name[0] = '\0';

    state->ball.x = WIN_X / 2;
    state->ball.y = WIN_Y / 2;
    state->ball.vx = BALL_VX;
    state->ball.vy = BALL_VY;
    state->ball.r = BALL_R;

    state->paddle.width = PADDLE_W;
    state->paddle.height = PADDLE_H;
    state->paddle.x = WIN_X / 2 - state->paddle.width / 2;
    state->paddle.y = WIN_Y * 0.9;

    srand(time(NULL));
    for (int i = 0; i < MAX_BLOCKS; ++i){
        int col = i % 10;
        int row = i / 10;

        state->blocks[i].width = BLOCK_W;
        state->blocks[i].height = BLOCK_H;
        state->blocks[i].x = 10 + col * state->blocks[i].width;
        state->blocks[i].y = 50 + row * (state->blocks[i].height + 10);
        state->blocks[i].hp = rand()%2;
    }
}


void game_update (GameState* state, float dt)
{
    if (state->gamescreen != GAME)
        return;

    state->ball.x += state->ball.vx * dt;
    state->ball.y += state->ball.vy * dt;

    /* Walls */

    if (state->ball.x + state->ball.r >= WIN_X) {
        state->ball.x = WIN_X - state->ball.r;
        state->ball.vx = -fabsf(state->ball.vx);
    }

    if (state->ball.x - state->ball.r <= 0) {
        state->ball.x = state->ball.r;
        state->ball.vx = fabsf(state->ball.vx);
    }

    if (state->ball.y - state->ball.r <= 0) {
        state->ball.y = state->ball.r;
        state->ball.vy = fabsf(state->ball.vy);
    }

    if (state->ball.y + state->ball.r >= WIN_Y) {
        state->is_running = false;
        return;
    }


    /* Paddle */

    float paddle_left   = state->paddle.x;
    float paddle_right  = state->paddle.x + state->paddle.width;
    float paddle_top    = state->paddle.y;
    float paddle_bottom = state->paddle.y + state->paddle.height;

    float ball_left   = state->ball.x - state->ball.r;
    float ball_right  = state->ball.x + state->ball.r;
    float ball_top    = state->ball.y - state->ball.r;
    float ball_bottom = state->ball.y + state->ball.r;

    if (
        ball_right >= paddle_left &&
        ball_left <= paddle_right &&
        ball_bottom >= paddle_top &&
        ball_top <= paddle_bottom &&
        state->ball.vy > 0
    ) {
        state->ball.y = paddle_top - state->ball.r;
        state->ball.vy = -fabsf(state->ball.vy);
    }

    if (paddle_right > WIN_X)
        state->paddle.x = WIN_X - state->paddle.width;

    if (paddle_left < 0) 
        state->paddle.x = 0;

    /* Blocks */

    for (int i = 0; i < MAX_BLOCKS; ++i) {

        if (state->blocks[i].hp <= 0)
            continue;

        float block_left   = state->blocks[i].x;
        float block_right  = state->blocks[i].x + state->blocks[i].width;
        float block_top    = state->blocks[i].y;
        float block_bottom = state->blocks[i].y + state->blocks[i].height;

        ball_left   = state->ball.x - state->ball.r;
        ball_right  = state->ball.x + state->ball.r;
        ball_top    = state->ball.y - state->ball.r;
        ball_bottom = state->ball.y + state->ball.r;

        if (
            ball_right >= block_left &&
            ball_left <= block_right &&
            ball_bottom >= block_top &&
            ball_top <= block_bottom
        ) {
            float overlap_x =
                fminf(ball_right, block_right) -
                fmaxf(ball_left, block_left);

            float overlap_y =
                fminf(ball_bottom, block_bottom) -
                fmaxf(ball_top, block_top);

            if (overlap_x < overlap_y) {

                /* Collision from left/right */

                if (state->ball.x < block_left) {
                    state->ball.x = block_left - state->ball.r;
                    state->ball.vx = -fabsf(state->ball.vx);
                } else {
                    state->ball.x = block_right + state->ball.r;
                    state->ball.vx = fabsf(state->ball.vx);
                }

            } else {

                /* Collision from top/bottom */

                if (state->ball.y < block_top) {
                    state->ball.y = block_top - state->ball.r;
                    state->ball.vy = -fabsf(state->ball.vy);
                } else {
                    state->ball.y = block_bottom + state->ball.r;
                    state->ball.vy = fabsf(state->ball.vy);
                }
            }

            state->blocks[i].hp--;
            state->score++;

            /* One block per frame */
            break;
        }
    }


    /* Check whether blocks remain */

    int block_alive = 0;

    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (state->blocks[i].hp > 0)
            block_alive++;
    }

    if (block_alive == 0)
        game_init(state, false);
}


void game_handle_input(GameState* state, const Uint8* keys, float dt)
{
    if (keys[SDL_SCANCODE_LEFT])
        state->paddle.x -= PADDLE_VX * dt;
    if (keys[SDL_SCANCODE_RIGHT])
        state->paddle.x += PADDLE_VX * dt;
}


void game_handle_click(GameState* state, int mouse_x, int mouse_y)
{
    if (state->gamescreen == MENU) {
        if (
            mouse_x >= GAME_BUTTON_X &&
            mouse_x <= GAME_BUTTON_X + GAME_BUTTON_W &&
            mouse_y >= GAME_BUTTON_Y &&
            mouse_y <= GAME_BUTTON_Y + GAME_BUTTON_H
        )
            state->gamescreen = GAME;
        if (
            mouse_x >= RECORD_BUTTON_X &&
            mouse_x <= RECORD_BUTTON_X + RECORD_BUTTON_W &&
            mouse_y >= RECORD_BUTTON_Y &&
            mouse_y <= RECORD_BUTTON_Y + RECORD_BUTTON_H
        )
            state->gamescreen = RECORD;
    }

    if (
        mouse_x >= PAUSE_BUTTON_X &&
        mouse_x <= PAUSE_BUTTON_X + PAUSE_BUTTON_W &&
        mouse_y >= PAUSE_BUTTON_Y &&
        mouse_y <= PAUSE_BUTTON_Y + PAUSE_BUTTON_H
    ) {
        if (state->gamescreen == GAME)
            state->gamescreen = PAUSE;
        else if (state->gamescreen == PAUSE)
            state->gamescreen = GAME;
    }

    if (
        state->gamescreen == RECORD &&
        mouse_x >= BACK_BUTTON_X &&
        mouse_x <= BACK_BUTTON_X + BACK_BUTTON_W &&
        mouse_y >= BACK_BUTTON_Y &&
        mouse_y <= BACK_BUTTON_Y + BACK_BUTTON_H
    )
        state->gamescreen = MENU;
}


void game_save(Leaderboard* board)
{
    FILE* file = fopen(SCORES_FILE,"w");
    if (file == NULL)
        return;
    for (int i = 0; i < board->count_scores; ++i)
        fprintf(file,"%s,%hd ",board->scores[i].name, board->scores[i].score);
    fclose(file);
}


void game_loading(Leaderboard* board)
{
    FILE* file = fopen(SCORES_FILE, "r");
    if (file == NULL) {
        board->count_scores = 0;
        return;
    }

    int i;
    for (i = 0;
        i < MAX_SCORES &&
        fscanf(file, "%s,%hd ",
               board->scores[i].name,
               &(board->scores[i].score)) == 2;
        ++i);
    board->count_scores = i;
    fclose(file);
}


void game_leaderboard(Leaderboard* board, const char * name, short score)
{
    if (board->count_scores < MAX_SCORES) {
        for (int i = 0; i< board->count_scores; ++i)
            if (
                strcmp(board->scores[i].name,name) == 0
                && board->scores[i].score < score
            ) {
                board->scores[i].score = score;
                return;
            }

        strcpy(board->scores[board->count_scores].name,name);
        board->scores[board->count_scores].score = score;
        board->count_scores++;
    }
}


void game_sort(Leaderboard* board)
{
    for (int i = 0; i < board->count_scores - 1; ++i)
        for (int j = 0; j < board->count_scores - 1 - i; ++j)
            if (board->scores[j].score > board->scores[j+1].score){
                ScoreEntry temp = board->scores[j];
                board->scores[j] = board->scores[j+1];
                board->scores[j+1] = temp;
            }
}


void game_text_handle_input(GameState* state, const char* text, bool enter) {
   if (state->gamescreen != NAME_INPUT)
       return;
   if (enter && strlen(state->player_name)!=0) {
      state->gamescreen = MENU;
   }
   if (!enter) strcat(state->player_name,text);
}