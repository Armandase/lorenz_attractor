#include "../inc/simulation.hpp"
#include "../inc/Attractor.hpp"
#include <algorithm>

int main(void){
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDL_Error("Failed to init SDL:", NULL, NULL);
    if (TTF_Init() == -1)
        SDL_Error("Failed to init TTF:", NULL, NULL);
    
    SDL_Window *window = SDL_CreateWindow("Gravity-simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
        SDL_Error("Failed to create SDL window:", window, NULL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        SDL_Error("Failed to create SDL renderer:", window, renderer);


    bool quit = false;
    SDL_Event e;
    Attractor lorenz;

    while (!quit)
    {
        lorenz.updateForDuration(10);
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)
                    quit = true;
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}