#include <SDL.h>
#include <stdio.h>
#include "../include/sdl_loop.h"


void sdl_loop()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fputs(SDL_GetError(), stderr);
        return;
    }

    SDL_Window* window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIN_X, WIN_Y,
                                       SDL_WINDOW_SHOWN);
    if (!window) {
        fputs(SDL_GetError(), stderr);
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fputs(SDL_GetError(), stderr);
        return;
    }

    SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
