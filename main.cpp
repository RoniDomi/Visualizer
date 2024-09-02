#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

using namespace std;

// Constant variables such as window dimensions, scale of 
// Shape vertexes and the fov/focal length of the "camera" 
const int WIDTH = 800, HEIGHT = 600;
const int scale = 100;
const float focalLength = 5.0f;

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

// Vector of type Edge that contains all the edges between vertices of the cube
// The ints in the Edge struct, represent the index of the cube vertices
// as they are listed in the cube vector.
vector<Edge> cubeEdges =
{
    Edge(0, 1), Edge(0, 3), Edge(0, 4), Edge(1, 2), Edge(1, 5), Edge(2, 3), 
    Edge(2, 6), Edge(3, 7), Edge(4, 5), Edge(4, 7), Edge(5, 6), Edge(6, 7) 
};

// Vector that contains all the 2D coordinates of the 3D shapes
vector<Point2D> projectedPoints;

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
        SDL_Point vertex;
        float pX = (WIDTH / 2) + (point.x * focalLength) / (focalLength + point.z) * scale;
        float pY = (HEIGHT / 2) + (point.y * focalLength) / (focalLength + point.z) * scale;

        // Append projected Point2D to projjection vector
        projectedPoints.push_back(Point2D(pX, pY));
    }
}

void drawShape(SDL_Renderer *renderer)
{
    for (const auto& edge : cubeEdges)
    {
        int x1 = projectedPoints[edge.vertexOne].x;
        int y1 = projectedPoints[edge.vertexOne].y;
        int x2 = projectedPoints[edge.vertexTwo].x;
        int y2 = projectedPoints[edge.vertexTwo].y;

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void rotateShape() 
{

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
        cout << "Could not create window: " << SDL_GetError() << endl;
        
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

        // Set render color to black and reset background & renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set renderer color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        addProjectetPoints();
        drawShape(renderer);
        
        SDL_RenderPresent(renderer);        
    }

    // If code reaches this point, while loop is broken by user thus making the program exit succesful
    SDL_DestroyWindow(window);
    SDL_QUIT;

    return EXIT_SUCCESS;
} 