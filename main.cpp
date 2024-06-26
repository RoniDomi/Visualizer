#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

const int WIDTH = 800, HEIGHT = 600;
const int scale = 100;
const float focalLength = 10.0f;

// Struct of a 2D vector with x,y coordinates
struct Point2D {
    int x;
    int y;

    // Constructor for the Point2D struct for ease of use
    Point2D(int x, int y) : x(x), y(y) {};
};

// Struct of a 3D vector with x,y,z coordinates
struct Point3D {
    int x;
    int y;
    int z;

    // Constructor for the Point3D struct for ease of use
    Point3D(int x, int y, int z) : x(x), y(y), z(z) {};
};

// Vector of type Point 3d which holds all the vertices of the cube
std::vector<Point3D> cube = 
{
    Point3D(-1, -1, 1), Point3D(1, -1, 1), Point3D(1, 1, 1), Point3D(-1, 1, 1), 
    Point3D(-1, -1, -1), Point3D(1, -1, -1), Point3D(1, 1, -1), Point3D(-1, 1, -1) 
};

int main(int argc, char *argv[])
{
    // Setup SDL window and renderer, basic variables following documentation guidelines.
    SDL_Init(SDL_INIT_EVERYTHING);    

    SDL_Window *window = SDL_CreateWindow("Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    

    // Return the respective error if program is unable to launch a window
    if (NULL == window) 
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        
        return 1;
    }

    // Window event variable will be used to detect if user requests to close window
    SDL_Event windowEvent;

    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            // Check if event type requested is terminate
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }

        // Set render color to black and reset renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set renderer color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderPresent(renderer);
    }

    // If code reaches this point while loop is broken by user thus making the runtime succesful
    SDL_DestroyWindow(window);
    SDL_QUIT;

    return EXIT_SUCCESS;
} 