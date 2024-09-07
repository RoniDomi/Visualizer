#include <iostream>
#include "window.cpp"

using namespace std;

int main(int argc, char *argv[])
{

    // Setup SDL window and renderer, basic variables following documentation guidelines.
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    WindowFrame frame = WindowFrame();

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

        frame.renderShape(renderer);
    }

    // If code reaches this point, while loop is broken by user thus making the program exit succesful
    SDL_DestroyWindow(window);
    SDL_QUIT;

    return EXIT_SUCCESS;
}