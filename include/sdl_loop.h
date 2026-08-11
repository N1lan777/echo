#pragma once

#include <SDL.h>
#include "game.h"
#include "vars.h"


void render_record(SDL_Renderer* renderer);
void draw_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius);
void render_menu(SDL_Renderer* renderer);
void render_game(GameState* state, SDL_Renderer* renderer, const SDL_Color blocks_color[]);
void render_name_input(SDL_Renderer* renderer, char* name);
