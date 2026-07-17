#include "game.h"
#include "stdio.h"
 void game_init(GameState* state){ 
    state -> score = 0;
    state -> is_running = true;
    state -> gamescreen = MENU; 

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
   if (state->gamescreen != GAME) {
        return;
    }
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
   
   if (state->ball.x >=state->paddle.x && state->ball.x <=paddle_right && state->ball.y>=state->paddle.y && state->ball.y <=paddle_bottom && state->ball.vy > 0){
      state->ball.vy = -(state->ball.vy);
   }
   for (int i = 0; i < MAX_BLOCKS; ++i){  
      if(state->blocks[i].hp > 0 ){
         float block_right = state->blocks[i].x + state->blocks[i].width;
         float block_bottom = state->blocks[i].y + state->blocks[i].height;
         
         if (state->ball.x >=state->blocks[i].x && state->ball.x <=block_right && state->ball.y>=state->blocks[i].y && state->ball.y <=block_bottom && state->ball.vy > 0){
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
void game_handle_click(GameState* state, int mouse_x, int mouse_y) {
   if (state->gamescreen == MENU) {
      if (mouse_x >= 350 && mouse_x <= 450 && mouse_y >= 250 && mouse_y <= 300){
         state -> gamescreen = GAME;
      }
      if (mouse_x >= 350 && mouse_x <= 450 && mouse_y >= 190 && mouse_y <=240){
         state -> is_running = false;
      }
   }
   if (mouse_x >=10 && mouse_x <=40 && mouse_y >=550 && mouse_y <=580 ){
      if (state -> gamescreen == GAME){
         state -> gamescreen = PAUSE;
      }
      else if (state -> gamescreen == PAUSE ){
         state -> gamescreen = GAME;
      }
   }
}
void game_save (Leaderboard* board){
   FILE* file =  fopen(SCORES_FILE,"w");
   if (file == NULL){
      return;
   }
   for (int i = 0 ; i < board->count_scores; ++i){
      fprintf(file,"%s,%d ",board->scores[i].name, board->scores[i].score);
   }
   fclose(file);
}
void game_loading(Leaderboard* board){
   FILE* file = fopen(SCORES_FILE,"r");
   if (file == NULL){
      board -> count_scores = 0;
      return;
   }
   int i;
   for (i = 0; i < MAX_SCORES && fscanf(file,"%s,%hd ", board -> scores[i].name, &(board -> scores[i].score)) == 2; ++i){
   }
   board->count_scores = i;

   fclose(file);
}