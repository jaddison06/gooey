#include "Gooey.h"

Gooey::Gooey(const char *title, const char *fontFile, CallbackAccepter *parent)
{
    this->parent = parent;

    windowManager = new WindowManager(title, fontFile);
}

Gooey::~Gooey()
{
    delete windowManager;
}

coord2d Gooey::getWindowDimensions()
{
    return windowManager->getWindowDimensions();
}

void Gooey::setFullscreen(bool fullscreen)
{
    windowManager->setFullscreen(fullscreen);
}

void Gooey::setWindowBorderVisible(bool visible)
{
    windowManager->setWindowBorderVisible(visible);
}

void Gooey::addComponent(Drawable *component)
{
    windowManager->addComponent(component);
}

GOOEY_STATUS_CODE Gooey::start()
{
    GOOEY_STATUS_CODE windowManagerStatus = GOOEY_SUCCESS;
    GOOEY_STATUS_CODE renderWindowStatus = GOOEY_SUCCESS;

    SDL_Event event;

    long frameCount = 0;

    auto start = std::chrono::high_resolution_clock::now();
    while (
        windowManagerStatus == GOOEY_SUCCESS &&
        renderWindowStatus == GOOEY_SUCCESS &&
        !quitFlag
    )
    {
        //printf("tick %i\n", frameCount);
        // we could go over event queue & handle 'em all, but that doesn't
        // always work. i'm not entirely sure why.
        //
        // instead, we just spam the sHIT out of everything by repeatedly polling,
        // whether there's something happening or not.

        //while (SDL_PollEvent(&event))
        SDL_PollEvent(&event);
        {
            parent->doCallback("gooey", &event);
            windowManagerStatus = tick(&event);
            renderWindowStatus = windowManager->render(&event);
        }


        frameCount ++;
    }
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double fps = frameCount / (duration.count() / pow(10, 6));

    //printf("average fps: %f\n", fps);

    // if something went wrong w/ render, return that. otherwise, return the wm status
    return renderWindowStatus != GOOEY_SUCCESS ? renderWindowStatus : windowManagerStatus;
}

GOOEY_STATUS_CODE Gooey::tick(SDL_Event *event)
{
    switch(event->type)
    {
        case SDL_QUIT:
        {
            return GOOEY_QUIT;
        }
        break;
        case SDL_WINDOWEVENT:
        {
            if (event->window.event == SDL_WINDOWEVENT_RESIZED)
            {
                windowManager->resizeWindow(event->window.data1, event->window.data2);
            }
        }
    }

    GOOEY_STATUS_CODE r = windowManager->tick(event);

    return r;
}

void Gooey::quit()
{
    quitFlag = true;
}