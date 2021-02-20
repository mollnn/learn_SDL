#include <bits/stdc++.h>
#include "SDL2/SDL.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Draw Pixel", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event e;
    //For tracking if we want to quit

    int i = 0;
    bool quit = false;
    while (!quit)
    {
        //Read any events that occured, for now we'll just quit if any event occurs
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, (i >> 16) & 255, (i >> 8) & 255, i & 255, 255);
        for (int x = 0; x < 800; x++)
        {
            for (int y = 0; y < 600; y++)
            {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
        SDL_RenderPresent(renderer);
        ++i;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}