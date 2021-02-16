#pragma once

#include "src/graphics/RenderWindow.h"
#include "src/graphics/Drawable.h"
#include <vector>


// The WindowManager handles everything to do with the RenderWindow.
// This includes resizing, minimizing, and drawing high-level stuff
//
// There are two base classes that the WindowManager can draw:
// - A Component (currently called Drawable) is something not part of normal operation,
// eg the status bar, or a dialogue box.
//
// - A Window (not implemented yet) is a section that the user will use as part of their
// actual workflow, and as such can be resized, moved, and added/deleted.

class WindowManager: public Tickable
{
    public:
        WindowManager(const char *title, const char *fontFile);
        ~WindowManager();

        coord2d getWindowDimensions();
        coord2d percentage(int percentage);

        GOOEY_STATUS_CODE tick(SDL_Event *event);
        GOOEY_STATUS_CODE render(SDL_Event *event);

        void addComponent(Drawable *component);

        void setFullscreen(bool fullscreen);
        void setWindowBorderVisible(bool visible);

        void resizeWindow(int width, int height);
    
    private:
        std::vector<Drawable *> components;
        RenderWindow *renderWindow;

};