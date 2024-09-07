#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <chrono>
#include "shape.cpp"

using namespace std;

/*  
    Constant variables such as window dimensions, scale of 
    shape vertexes and the fov/focal length of the "camera" 
*/
float DeltaTime = 0.0f;
float rotation = 0.0f;

// Available shapes

// CUBE
vector<Point3D> cubeVertex = 
{
    Point3D(-1.0f, -1.0f, 1.0f), Point3D(1.0f, -1.0f, 1.0f), Point3D(1.0f, 1.0f, 1.0f), Point3D(-1.0f, 1.0f, 1.0f), 
    Point3D(-1.0f, -1.0f, -1.0f), Point3D(1.0f, -1.0f, -1.0f), Point3D(1, 1, -1), Point3D(-1.0f, 1.0f, -1.0f) 
};

vector<Edge> cubeEdges = 
{
    Edge(0, 1), Edge(0, 3), Edge(0, 4), Edge(1, 2), Edge(1, 5), Edge(2, 3), 
    Edge(2, 6), Edge(3, 7), Edge(4, 5), Edge(4, 7), Edge(5, 6), Edge(6, 7) 
};

class WindowFrame{
    public: 
        WindowFrame() {}

        void renderShape(SDL_Renderer *renderer) 
        {
            auto time1 = chrono::high_resolution_clock::now();
                chrono::duration<double> duration(0);
                Shape shape = Shape();

                // Set render color to black and reset background & renderer
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                // Set renderer color to white
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                rotation += 1 * DeltaTime;

                for (auto& edge: cubeEdges) 
                {
                    Point3D rotatedStartPoint = shape.rotateShapeX(shape.rotateShapeY(cubeVertex[edge.vertexOne], rotation), rotation);
                    Point3D rotatedEndPoint = shape.rotateShapeX(shape.rotateShapeY(cubeVertex[edge.vertexTwo], rotation), rotation);
                    Point2D projectedStart = shape.projectPoint(rotatedStartPoint);
                    Point2D projectedEnd = shape.projectPoint(rotatedEndPoint);
                    SDL_RenderDrawLine(renderer, projectedStart.x, projectedStart.y, projectedEnd.x, projectedEnd.y);
                }
                
                SDL_RenderPresent(renderer);        

                auto time2 = chrono::high_resolution_clock::now();
                duration = time2 - time1;
                DeltaTime = duration.count();
                time1 = time2;
        }
};