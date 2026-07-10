#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
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

    bool running = true;
    SDL_Rect rect = (SDL_Rect) {
        .x = (int)WIN_X / 2,
        .y = (int)WIN_Y / 2,
        .w = 50,
        .h = 50,
    };

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type)
                case SDL_QUIT:
                    running = false;
                    break;
        }

        if (!running) break;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // SDL_Delay(10);

        // SDL_SetRenderDrawColor(renderer, rand()%255, rand()%255, rand()%255, 255);
        // SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
