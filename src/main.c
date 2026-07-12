#include "game.h"
#include <SDL.h>

int main(int argc, char* argv[]) {
    GameState state;
    game_init(&state);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("echo", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    Uint32 last_time = SDL_GetTicks();
    while (state.is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state.is_running = false;
            }
        }
        Uint32 Now_time = SDL_GetTicks();
        float dt    = (Now_time - last_time)/ 1000.0f ;
        last_time = Now_time;

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        game_handle_input(&state, keys, dt);
        game_update(&state, dt);

        // TODO: render(&state, renderer); — Alegen добавляет здесь свой вызов рендера
        
        SDL_Delay(16);

    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}