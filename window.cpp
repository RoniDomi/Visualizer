#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <chrono>
#include "shape.h"

using namespace std;

/*  
    Constant variables such as window dimensions, scale of 
    shape vertexes and the fov/focal length of the "camera" 
*/
const int WIDTH = 800, HEIGHT = 600;
float DeltaTime = 0.0f;
float rotation = 0.0f;

class Window{
    public: 
        Window() 
        {
            createWindow();
        }

        void renderShape(SDL_Renderer *renderer, Shape shape) 
        {
            auto time1 = chrono::high_resolution_clock::now();
                chrono::duration<double> duration(0);

                // Set render color to black and reset background & renderer
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                // Set renderer color to white
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                rotation += 1 * DeltaTime;

                for (auto& edge: ) 
                {
                    rotatedStartPoint = rotateShapeX(rotateShapeY(cube[edge.vertexOne]));
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

        c
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


            }
            // If code reaches this point, while loop is broken by user thus making the program exit succesful
            SDL_DestroyWindow(window);
            SDL_QUIT;

            return EXIT_SUCCESS;
        }
};