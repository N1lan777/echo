#include "game.h"
#include "stdio.h"
 void game_init(GameState* state){
    state -> score = 0;
    state -> is_running = true;

    state -> ball.x = 400;
    state -> ball.y = 300;
    state -> ball.vx = 50;
    state -> ball.vy = 50;

    state -> paddle.x = 375;
    state -> paddle.y = 550;
    state -> paddle.width = 50;
    state -> paddle.height = 25;

    for (int i = 0; i < MAX_BLOCKS; ++i){
      int col = i % 10;
      int row = i / 10;
      state -> blocks[i].x = 10 + col * 75;
      state -> blocks[i].y = 50 + row * (25 + 10) ;
      state -> blocks[i].width = 75;
      state -> blocks[i].height = 25;
      state -> blocks[i].hp = 1;
    }
 }

void game_update (GameState * state, float dt){
   state -> ball.x = state -> ball.x + state -> ball.vx * dt;
   state -> ball.y = state -> ball.y + state -> ball.vy * dt;
   if (state->ball.x >= 800 || state->ball.x <= 0) {
      state->ball.vx = -(state->ball.vx);
   }
   if (state->ball.y >= 600 || state->ball.y <= 0) {
      state->ball.vy = -(state->ball.vy);
   }
}
void game_handle_input(GameState* state, const Uint8* keys, float dt){
   if (keys[SDL_SCANCODE_LEFT]){
      state -> paddle.x -= 300 * dt;
   }
   if (keys[SDL_SCANCODE_RIGHT]){
      state -> paddle.x += 300 * dt;
   }
}