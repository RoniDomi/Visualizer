#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

// Constant variables such as window dimensions, scale of 
// Shape vertexes and the fov/focal length of the "camera" 
const int WIDTH = 800, HEIGHT = 600;
const int scale = 100;
const float focalLength = 5.0f;
float rotation = 0.0f;
float DeltaTime = 0.0f;

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

/*
    Calculate the projected x & y value for the given point
    using the formula of weak-perspective projection

    Formula for Px/Py = X/Y * Fov / Fov + Z
    Add half the window height/width to centre it on window
    and multiply by scale to increase vertex size for better
    visibility
*/
Point2D projectPoint(Point3D point)
{
    Point2D returnPoint = Point2D(0, 0);
    returnPoint.x = (WIDTH / 2) + (point.x * focalLength) / (focalLength + point.z) * scale;
    returnPoint.y = (HEIGHT / 2) + (point.y * focalLength) / (focalLength + point.z) * scale;

    return returnPoint;
}

Point3D rotateShapeY(Point3D point) 
{
    Point3D returnPoint = Point3D(0, 0, 0);
    returnPoint.x = cos(rotation) * point.x - sin(rotation) * point.z;
    returnPoint.y = point.y;
    returnPoint.z = sin(rotation) * point.x + cos(rotation) * point.z;

    return returnPoint;
}

Point3D rotateShapeX(Point3D point) 
{
    Point3D returnPoint = Point3D(0, 0, 0);
    returnPoint.y = cos(rotation) * point.y - sin(rotation) * point.z;
    returnPoint.x = point.x;
    returnPoint.z = sin(rotation) * point.y + cos(rotation) * point.z;

    return returnPoint;
}

void renderShape(SDL_Renderer *renderer) 
{
    auto time1 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration(0);

        // Set render color to black and reset background & renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set renderer color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        rotation += 1 * DeltaTime;

        for (auto& edge: cubeEdges) 
        {
            Point3D rotatedStartPoint = rotateShapeX(rotateShapeY(cube[edge.vertexOne]));
            Point3D rotatedEndPoint = rotateShapeX(rotateShapeY(cube[edge.vertexTwo]));
            Point2D projectedStart = projectPoint(rotatedStartPoint);
            Point2D projectedEnd = projectPoint(rotatedEndPoint);
            SDL_RenderDrawLine(renderer, projectedStart.x, projectedStart.y, projectedEnd.x, projectedEnd.y);
        }
        
        SDL_RenderPresent(renderer);        

        auto time2 = chrono::high_resolution_clock::now();
        duration = time2 - time1;
        DeltaTime = duration.count();
        time1 = time2;
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

        renderShape(renderer);

    }
    // If code reaches this point, while loop is broken by user thus making the program exit succesful
    SDL_DestroyWindow(window);
    SDL_QUIT;

    return EXIT_SUCCESS;
} 