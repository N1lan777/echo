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
 }