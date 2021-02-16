#pragma once

#include "graphics/Drawable.h"

class Text: public Drawable
{
    public:
        Text(int x, int y, const char *text, Col col);

        GOOEY_STATUS_CODE tick(SDL_Event *event);
    
    private:
        int x, y;
        const char *text;
        Col col;
};