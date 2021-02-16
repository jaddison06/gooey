#include "src/graphics/widgets/Button.h"

Button::Button(int x, int y, int w, int h, Col col, const char *name, CallbackAccepter *parent)
{
    this->minimums = {x, y};
    this->maximums = {x + w, y + h};
    this->col = col;
    this->name = name;
    this->parent = parent;

}

GOOEY_STATUS_CODE Button::tick(SDL_Event *event)
{
    //printf("Drawing button %s\n", name);
    ctx.renderWindow->fillRect(minimums, maximums, col);

    // if the mouse goes down inside the button, we're pressed.
    // when the mouse gets released, we're not pressed.
    // if the mouse release is also inside the button, fire the callback.

    // TODO: the first press takes a while to register. why????
    // also todo: proper resizable window with dynamic resizing (based on POSITION_TYPE)

    if (event->type == SDL_MOUSEBUTTONDOWN && clickInButton(event))
    {
        //printf("Button pressed\n");
        isPressed = true;
    } else if (event->type == SDL_MOUSEBUTTONUP && isPressed)
    {
        //printf("Button released\n");
        isPressed = false;
        if (clickInButton(event))
        {
            //printf("Button clicked\n");
            parent->doCallback(name, event);
        }
    }

    return GOOEY_SUCCESS;
}

bool Button::clickInButton(SDL_Event *event)
{
    return (event->button.x > minimums.x && event->button.x < maximums.x && event->button.y > minimums.y && event->button.y < maximums.y);
}

bool Button::getIsPressed()
{
    return isPressed;
}

void Button::setCol(Col col)
{
    //printf("setting colour\n");
    this->col = col;
}