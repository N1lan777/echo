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
   if (state->ball.y <= 0) {
      state->ball.vy = -(state->ball.vy);
   }
   if (state->ball.y >= 600){
      state->is_running = false;
   }

   float paddle_right = state->paddle.width + state->paddle.x;
   float paddle_bottom = state->paddle.height + state->paddle.y;  
   
   if (state->ball.x >=state->paddle.x && state->ball.x <=paddle_right && state->ball.y>=state->paddle.y && state->ball.y <=paddle_bottom){
      state->ball.vy = -(state->ball.vy);
   }
   for (int i = 0; i < MAX_BLOCKS; ++i){  
      if(state->blocks[i].hp > 0 ){
         float block_right = state->blocks[i].x + state->blocks[i].width;
         float block_bottom = state->blocks[i].y + state->blocks[i].height;
         if (state->ball.x >=state->blocks[i].x && state->ball.x <=block_right && state->ball.y>=state->blocks[i].y && state->ball.y <=block_bottom){
            state->ball.vy = -(state->ball.vy);
            state->blocks[i].hp--;
         }
      }
   }
   int block_alive = 0;
   for (int i = 0; i < MAX_BLOCKS; ++i){
      if (state->blocks[i].hp > 0){
         block_alive++;
      }
   }
   if (block_alive == 0){
      state->won = true;

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