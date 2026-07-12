#pragma once


#include <SDL.h>
#include "game.h"


#define GAME_TITLE "echo"
#define WIN_X 800
#define WIN_Y 600


void render(GameState* state, SDL_Renderer* renderer, const SDL_Color blocks_color[]);
