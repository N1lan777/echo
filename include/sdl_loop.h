#pragma once


#include <SDL.h>
#include "game.h"


#define GAME_TITLE "echo"
#define WIN_X 1024
#define WIN_Y 768


void render(GameState* state, SDL_Renderer* renderer);
