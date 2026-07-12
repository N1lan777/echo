#include <SDL2/SDL.h>
#include <stdio.h>
#include "game.h"
#include "sdl_loop.h"


int main(int argc, char* argv[]) {
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

    Uint32 last_time = SDL_GetTicks();
    while (state.is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state.is_running = false;
                break;
            }
        }

        if (!state.is_running) break;

        Uint32 Now_time = SDL_GetTicks();
        float dt    = (Now_time - last_time)/ 1000.0f ;
        last_time = Now_time;

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        game_handle_input(&state, keys, dt);
        game_update(&state, dt);

        render(&state, renderer);
        
        SDL_Delay(16);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
