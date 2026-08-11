#include <SDL.h>
#include <stdio.h>
#include "game.h"
#include "sdl_loop.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    GameState state;
    Leaderboard board;
    game_init(&state,true);
    game_loading(&board);

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
        blocks_color[i].r = rand()%256;
        blocks_color[i].g = rand()%256;
        blocks_color[i].b = rand()%256;
        blocks_color[i].a = rand()%256;
    }


    SDL_StartTextInput();
    Uint32 last_time, Now_time;
    while (state.is_running) {
        switch (state.gamescreen) {
            case MENU:
    		    last_time = SDL_GetTicks();
                render_menu(renderer);
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
            case PAUSE:
    		    last_time = SDL_GetTicks();
                break;
            case RECORD:
                last_time = SDL_GetTicks();
                render_record(renderer);
                break;
            default:
                fputs("Catched undefined behavior\n", stderr);
                break;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN)
                game_handle_click(&state, event.button.x, event.button.y);

            if (event.type == SDL_QUIT) {
                state.is_running = false;
                break;
            }

            if (event.type == SDL_TEXTINPUT) {
                ;// game_text_handle_input(&state, event.text.text, false);
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                ;// game_text_handle_input(&state, "", true);
            }
        }   // https://www.youtube.com/watch?v=66xQ67ckWNQ

        if (!state.is_running) break;

        SDL_Delay(16);
    }

    game_leaderboard(&board,"player",state.score);
    game_sort(&board);
    game_save(&board);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
