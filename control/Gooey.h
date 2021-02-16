#pragma once

#include <SDL2/SDL.h>
#include "graphics/WindowManager.h"
#include "control/CallbackAccepter.h"
#include <vector>
#include <chrono>


class Gooey
{
    public:
        GOOEY_STATUS_CODE start();
        Gooey(const char *title, const char *fontFile, CallbackAccepter *parent);
        ~Gooey();

        void addComponent(Drawable *component);
        void quit();

        coord2d getWindowDimensions();
        void setFullscreen(bool fullscreen);
        void setWindowBorderVisible(bool visible);

    private:
        WindowManager *windowManager;
        CallbackAccepter *parent;

        // set this true to quit on next event cycle
        bool quitFlag = false;

        GOOEY_STATUS_CODE tick(SDL_Event *event);

};