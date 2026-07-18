#include <SDL.h>
#include <stdio.h>
#include "game.h"
#include "sdl_loop.h"
#include <stdlib.h>
#include <time.h>


int main(void) {
    GameState state;
    game_init(&state);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fputs(SDL_GetError(), stderr);
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow (
        GAME_TITLE,  SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WIN_X, WIN_Y,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        fputs(SDL_GetError(), stderr);
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fputs(SDL_GetError(), stderr);
        return -1;
    }

    srand(time(NULL));
    SDL_Color blocks_color[MAX_BLOCKS];
    for (int i = 0; i < MAX_BLOCKS; i++) {
        blocks_color[i].r = rand()%255;
        blocks_color[i].g = rand()%255;
        blocks_color[i].b = rand()%255;
        blocks_color[i].a = rand()%255;
    }

    SDL_Color color_game_b = (SDL_Color) {
        rand()%255,
        rand()%255,
        rand()%255,
        rand()%255
    };

    SDL_Color color_exit_b = (SDL_Color) {
        rand()%255,
        rand()%255,
        rand()%255,
        rand()%255
    };

    Uint32 last_time, Now_time;
    last_time = SDL_GetTicks();
    while (state.is_running) {
        switch (state.gamescreen) {
            case MENU:
                render_menu(renderer, &color_game_b, &color_exit_b);
                break;
            case GAME:
                Now_time = SDL_GetTicks();
                float dt = (Now_time - last_time) / 1000.0f ;
                last_time = Now_time;

                const Uint8* keys = SDL_GetKeyboardState(NULL);
                game_handle_input(&state, keys, dt);
                game_update(&state, dt);

                render_game(&state, renderer, blocks_color);
                break;
            default:
                fputs("Not a game and menu...", stderr);
                break;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state.is_running = false;
                break;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                game_handle_click(&state, event.button.x, event.button.y);
                break;
            }
        }

        if (!state.is_running) break;

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
