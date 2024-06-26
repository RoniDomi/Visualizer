#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

using namespace std;

// Constant variables such as window dimensions, scale of 
// Shape vertexes and the fov/focal length of the "camera" 
const int WIDTH = 800, HEIGHT = 600;
const int scale = 100;
const float focalLength = 10.0f;

// Struct of a 2D vector with x,y coordinates
struct Point2D {
    float x;
    float y;

    // Constructor for the Point2D struct for ease of use
    Point2D(float x, float y) : x(x), y(y) {};
};

// Struct of a 3D vector with x,y,z coordinates
struct Point3D {
    float x;
    float y;
    float z;

    // Constructor for the Point3D struct for ease of use
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {};
};

// Struct of an edge between to verteces 
struct Edge {
    int vertexOne;
    int vertexTwo;

    // Constructor for the Edge struct for ease of use
    Edge(int vertexOne, int vertexTwo) : vertexOne(vertexOne), vertexTwo(vertexTwo) {};
};

// Vector of type Point 3d which holds all the vertices of the cube
vector<Point3D> cube = 
{
    Point3D(-1.0f, -1.0f, 1.0f), Point3D(1.0f, -1.0f, 1.0f), Point3D(1.0f, 1.0f, 1.0f), Point3D(-1.0f, 1.0f, 1.0f), 
    Point3D(-1.0f, -1.0f, -1.0f), Point3D(1.0f, -1.0f, -1.0f), Point3D(1, 1, -1), Point3D(-1.0f, 1.0f, -1.0f) 
};

// Vector that contains all the 2D coordinates of the 3D shape
vector<Point2D> perspectiveProjection;

/*
    Calculate the projected x & y value for each point of the shape 
    using the formula of weak-perspective projection

    Formula for Px/Py = X/Y * Fov / Fov + Z
    Add half the window height/width to centre it on window
    and multiply by scale to increase vertex size for better
    visibility
*/
void addProjectetPoints()
{
    for (const auto& point : cube)
    {
        float pX = (WIDTH / 2) + (point.x * focalLength) / (focalLength + point.z) * scale;
        float pY = (HEIGHT / 2) + (point.y * focalLength) / (focalLength + point.z) * scale;

        // Append projected point to vector
        perspectiveProjection.push_back(Point2D(pX, pY));
    }
}

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
        int cnt = 0;

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

        addProjectetPoints();

        // Set renderer color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderPresent(renderer);

        cnt++;
        if (cnt > 1000) {break;}
    }

    // If code reaches this point while loop is broken by user thus making the runtime succesful
    SDL_DestroyWindow(window);
    SDL_QUIT;

    return EXIT_SUCCESS;
} 