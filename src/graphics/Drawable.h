#pragma once

#include "src/graphics/RenderWindow.h"
#include <SDL2/SDL.h>

// stuff that a Drawable might need
struct DrawableContext
{
    RenderWindow *renderWindow;
};

class Drawable: public Tickable
{
    public:
        void drawableInit(DrawableContext ctx);
    
    protected:
        DrawableContext ctx;
        // empty implementation, can be overridden by inheriters.
        virtual void afterInit() {};

};