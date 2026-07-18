#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include "sdl_loop.h"
#include "game.h"


// Func draw circle
void draw_circle(SDL_Renderer* renderer, int centerX, int centerY, int radius)
{
    int x = radius - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = tx - (radius << 1);

    while (x >= y) {
        SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
        SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
        SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);
        SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);

        if (error <= 0) {
            y++;
            error += ty;
            ty += 2;
        }

        else {
            x--;
            tx += 2;
            error += tx - (radius << 1);
        }
    }
}


// Func render
static inline void _render_impl(GameState* state, SDL_Renderer* renderer, const SDL_Color b_c[])
{   // Black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect block, paddle;

    paddle = (SDL_Rect) {
        state->paddle.x,
        state->paddle.y,
        state->paddle.width,
        state->paddle.height
    };

    for (int i = 0; i < MAX_BLOCKS; i++) {
        block = (SDL_Rect) {
            state->blocks[i].x,
            state->blocks[i].y,
            state->blocks[i].width,
            state->blocks[i].height
        };

        // Draw ball
        draw_circle(renderer, state->ball.x, state->ball.y, /* Test */ state->ball.r);
        // Draw one block
        SDL_SetRenderDrawColor(renderer, b_c[i].r, b_c[i].g, b_c[i].b, b_c[i].a);
        SDL_RenderFillRect(renderer, &block);
    }

    // Draw paddle
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
    SDL_RenderFillRect(renderer, &paddle);

    SDL_RenderPresent(renderer);
}


// Call func render
void render(GameState *state, SDL_Renderer *renderer, const SDL_Color b_c[])
{
    _render_impl(state, renderer, b_c);
}

