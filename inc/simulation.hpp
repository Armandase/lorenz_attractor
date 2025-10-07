#ifndef SIMULATION_HPP
# define SIMULATION_HPP

# include <SDL.h>
# include <exception>
# include <iostream>
# include <vector>
# include <SDL_ttf.h>
# include <SDL_image.h>

# define GRAVITY 1
# define SCREEN_HEIGHT 720
# define SCREEN_WIDTH 1080
# define PARTICLES 100
# define RED 255
# define GREEN 255
# define BLUE 0

void    SDL_Error(const std::string &mess, SDL_Window *window, SDL_Renderer *renderer);
void    render_empty(SDL_Renderer *renderer);
void    drawCircle(int centreX, int centreY, int radius, SDL_Renderer *renderer);

#endif // !SIMULATION_HPP