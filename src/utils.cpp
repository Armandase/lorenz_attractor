#include "../inc/simulation.hpp"

void    render_empty(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDL_Error(const std::string &mess, SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Log((mess + " %s").c_str(), SDL_GetError());
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window) {
        SDL_DestroyWindow(window);
        SDL_Quit(); 
    }
    exit(1);
}

void drawCircle(int centreX, int centreY, int radius, SDL_Renderer *renderer){
    int x = radius - 1;
    int y = 0;
    int dx = 1, dy = 1;
    int err = dx - (radius * 2);

    while (x >= y){
        SDL_RenderDrawLine(renderer, centreX + x, centreY - y, centreX + x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX - x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX + y, centreY - x, centreX + y, centreY + x);
        SDL_RenderDrawLine(renderer, centreX - y, centreY - x, centreX - y, centreY + x);
        if (err <= 0){
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius * 2);
        }
    }
}