#pragma once

#include "src/graphics/Drawable.h"
#include "src/control/CallbackAccepter.h"

class Button: public Drawable
{
    public:
        Button(int x, int y, int w, int h, Col col, const char *name, CallbackAccepter *parent);

        GOOEY_STATUS_CODE tick(SDL_Event *event);

        bool getIsPressed();
        void setCol(Col col);

    private:
        coord2d minimums, maximums;
        Col col;
        const char *name;
        CallbackAccepter *parent;

        bool isPressed = false;

        bool clickInButton(SDL_Event *event);

};