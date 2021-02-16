#pragma once

// Forward declarations for MyWidget - for more information on custom widgets, take a look at graphics/widgets/MyWidget.cpp

// standard stuff
#include "graphics/Drawable.h"
#include "control/CallbackAccepter.h"

#include "graphics/widgets/Button.h"

class MyWidget: public Drawable
{
    public:
        MyWidget(int x, int y, Col buttonCol, Col lineCol, const char *name, CallbackAccepter *parent);
        ~MyWidget();

        GOOEY_STATUS_CODE tick(SDL_Event *event);
    
    private:
        // Size of our button
        const int size = 25;

        Button *button;

        coord2d startPos, endPos;
        Col lineCol;
        Col buttonCol;

        void afterInit();
};