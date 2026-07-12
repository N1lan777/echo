#include <SDL2/SDL.h>
#include <stdbool.h>
#include "sdl_loop.h"
#include "game.h"


static void _render_impl(GameState* state, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void render(GameState *state, SDL_Renderer *renderer)
{
    _render_impl(state, renderer);
}

