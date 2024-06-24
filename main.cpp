#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

const int projectionMatrix[2][3] = 
{
    {1, 0, 0},
    {0, 1, 0}
};

const int scale = 100;

int cube[8][3] = {
    {-1, 1, 1},
    {1, -1, 1},
    {1, 1, 1},
    {-1, 1, 1},
    {-1, -1 , -1},
    {1, -1, -1},
    {1, 1, -1},
    {-1, 1, -1}
};

int multiplyProjection(int pMatrix[3][3], int vertex[1][3])
{
    int resultMatrix[1][2];
}


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);    

    SDL_Window *window = SDL_CreateWindow("Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    


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

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_QUIT;

    return EXIT_SUCCESS;
} 