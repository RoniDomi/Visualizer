#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window
{
    public:
        Window();
        void renderShape(SDL_Renderer *renderer, Shape shape);
        int createWindow();
};

#endif