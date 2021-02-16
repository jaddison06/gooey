#pragma once

#include <SDL2/SDL.h>
#include "control/constants.h"

class Tickable
{
    public:
        virtual GOOEY_STATUS_CODE tick(SDL_Event *event) = 0;
};