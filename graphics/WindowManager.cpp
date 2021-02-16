#include "graphics/WindowManager.h"

WindowManager::WindowManager(const char *title, const char *fontFile)
{
    renderWindow = new RenderWindow(title, fontFile);

}

WindowManager::~WindowManager()
{
    delete renderWindow;
    for (int i = 0; i < (int)components.size(); i++)
    {
        delete components.at(i);
    }
    components.clear();
}

void WindowManager::setFullscreen(bool fullscreen)
{
    renderWindow->setFullscreen(fullscreen);
}

void WindowManager::setWindowBorderVisible(bool visible)
{
    renderWindow->setWindowBorder(visible ? SDL_TRUE : SDL_FALSE);
}

void WindowManager::resizeWindow(int width, int height)
{
    renderWindow->resizeWindow(width, height);
}

coord2d WindowManager::getWindowDimensions()
{
    return renderWindow->getWindowDimensions();
}

coord2d WindowManager::percentage(int percentage)
{
    return {
        getWindowDimensions().x * (percentage / 100),
        getWindowDimensions().y * (percentage / 100)
    };
}

void WindowManager::addComponent(Drawable *component)
{
    component->drawableInit({renderWindow});
    components.push_back(component);
}

// this handles an event but DOESN'T render.
// the idea is that, if the event queue is phat, you can tick()
// over all the events you want, and then only render when you need to.
// you could also theoretically render in a separate thread.
//
// that causes flickering tho so don't try it
GOOEY_STATUS_CODE WindowManager::tick(SDL_Event *event)
{
    GOOEY_STATUS_CODE r = GOOEY_SUCCESS;
    for (auto component : components)
    {
        r = component->tick(event);
        if (r != GOOEY_SUCCESS) { return r; }
    }

    return r;
}

GOOEY_STATUS_CODE WindowManager::render(SDL_Event *event)
{
    auto r = renderWindow->tick(event);
    return r;
}