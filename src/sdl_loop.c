#include <SDL2/SDL.h>
#include <stdbool.h>
#include "sdl_loop.h"
#include "game.h"


static void _render_impl(GameState* state, SDL_Renderer* renderer, const SDL_Color b_c[])
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect r, p;

    p = (SDL_Rect) {
        state->paddle.x,
        state->paddle.y,
        state->paddle.width,
        state->paddle.height
    };
    
    for (int i = 0; i < MAX_BLOCKS; i++) {
        r = (SDL_Rect) {
            state->blocks[i].x,
            state->blocks[i].y,
            state->blocks[i].width,
            state->blocks[i].height
        };

        SDL_SetRenderDrawColor(renderer, b_c[i].r, b_c[i].g, b_c[i].b, b_c[i].a);
        SDL_RenderFillRect(renderer, &r);

        SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
        SDL_RenderFillRect(renderer, &p);
    }

    SDL_RenderPresent(renderer);
}

void render(GameState *state, SDL_Renderer *renderer, const SDL_Color b_c[])
{
    _render_impl(state, renderer, b_c);
}

