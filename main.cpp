#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Point cornerOne = {10, 10};
    SDL_Point cornerTwo = {10, 500};
    SDL_Point cornerThree = {500, 10};
    SDL_Point cornerFour = {500, 500};

    SDL_Point Line1[2] = {cornerOne, cornerTwo};
    SDL_Point Line2[2] = {cornerOne, cornerThree};
    SDL_Point Line3[2] = {cornerTwo, cornerFour};
    SDL_Point Line4[2] = {cornerThree, cornerFour};


    if (NULL == window) 
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        
        return 1;
    }

    SDL_Event windowEvent;

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLines(renderer, Line1, 2);
        SDL_RenderDrawLines(renderer, Line2, 2);
        SDL_RenderDrawLines(renderer, Line3, 2);
        SDL_RenderDrawLines(renderer, Line4, 2);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_QUIT;

    return EXIT_SUCCESS;
} 