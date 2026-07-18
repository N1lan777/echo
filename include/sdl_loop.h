#pragma once

#include <SDL.h>
#include "game.h"
#include "vars.h"

void draw_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius);
void render_menu(SDL_Renderer* renderer, const SDL_Color* cgb, const SDL_Color* ceb);
void render_game(GameState* state, SDL_Renderer* renderer, const SDL_Color blocks_color[]);
