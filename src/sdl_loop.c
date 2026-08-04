#include <SDL2/SDL.h>
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

// Func render pause
static inline void _render_pause_b_impl(SDL_Renderer* renderer)
{
    SDL_Rect pause_b = {
        PAUSE_BUTTON_X,
        PAUSE_BUTTON_Y,
        PAUSE_BUTTON_W,
        PAUSE_BUTTON_H
    };

    SDL_Color cpb = {
        255, 0, 0, 255
    };

    SDL_SetRenderDrawColor(renderer, cpb.r, cpb.g, cpb.b, cpb.a);
    SDL_RenderFillRect(renderer, &pause_b);
}

// Func render menu
static inline void _render_menu_impl(SDL_Renderer* renderer)
{   // Black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect game_b = {
        GAME_BUTTON_X,
        GAME_BUTTON_Y,
        GAME_BUTTON_W,
        GAME_BUTTON_H
    };

    SDL_Color cgb = {
        0, 0, 255, 255
    };

    _render_pause_b_impl(renderer);

    SDL_SetRenderDrawColor(renderer, cgb.r, cgb.g, cgb.b, cgb.a);
    SDL_RenderFillRect(renderer, &game_b);

    SDL_RenderPresent(renderer);
}

// Func render game
static inline void _render_game_impl(GameState* state, SDL_Renderer* renderer, const SDL_Color b_c[])
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
        draw_circle(renderer, state->ball.x, state->ball.y, state->ball.r);
        // Draw one block
        if (state->blocks[i].hp > 0) {
            SDL_SetRenderDrawColor(renderer, b_c[i].r, b_c[i].g, b_c[i].b, b_c[i].a);
            SDL_RenderFillRect(renderer, &block);
	}

        _render_pause_b_impl(renderer);
    }

    // Draw paddle
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
    SDL_RenderFillRect(renderer, &paddle);

    SDL_RenderPresent(renderer);
}


// Call func render game
void render_game(GameState *state, SDL_Renderer *renderer, const SDL_Color b_c[])
{
    _render_game_impl(state, renderer, b_c);
}

// Call func render menu
void render_menu(SDL_Renderer* renderer)
{
    _render_menu_impl(renderer);
}
