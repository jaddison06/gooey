#pragma once

#include <string>

class CallbackAccepter
{
    public:
        virtual void doCallback(std::string componentName, SDL_Event *event)=0;
    
};