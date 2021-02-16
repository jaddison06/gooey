// In this file we're going to define a custom widget, called MyWidget.
// It'll be a button with a cross in it.
// Our custom button will also change colour slightly when it's being pressed.

// Let's include the header with our forward declaration
#include "src/graphics/widgets/MyWidget.h"

// First, our constructor
MyWidget::MyWidget(int x, int y, Col buttonCol, Col lineCol, const char *name, CallbackAccepter *parent)
{
    // These positions track the corners of our button
    startPos = {x, y};
    endPos = {x + size, y + size}; // size was defined in the header

    // store our colours
    this->lineCol = lineCol;
    this->buttonCol = buttonCol;

    // We're going to use a Button for the actual click detection
    //
    // This isn't wrapped by Gooey - all the housekeeping usually happens in
    // addComponent, which we're not using. This means we have to initialize,
    // tick, and delete the button ourselves. More on that later.
    button = new Button(x, y, size, size, buttonCol, name, parent);

}

// Destructor
MyWidget::~MyWidget()
{
    delete button;
}

// You don't have to override this, but we're going to.
//
// ctx is a DrawableContext, which is a special struct that holds any
// info we might need at tick-time. By default, it only holds a RenderWindow,
// but you can add to it if there's something you want to dynamically pass
// to some or all of your widgets.
//
// drawableInit is a method that would normally get called by
// addComponent. It gives a component its context.
//
// We need to call the button's drawableInit, but we can't do that
// until we've got our own context, which happens in our own drawableInit.
// This means we can't init the button in our initializer.
// Luckily, Gooey provides the afterInit method. You can override it, but
// you don't have to. It gets called after a component's drawableInit.
//
// (If you're overriding a virtual method, remember to forward-declare it!)
void MyWidget::afterInit()
{
    button->drawableInit(ctx);
}

// Now the good bit!
GOOEY_STATUS_CODE MyWidget::tick(SDL_Event *event)
{
    // If the button's pressed, make it slightly darker

    // new colour for the button
    Col newCol;

    // how much to multiply each colour value by
    float colCoeff = 0.8;

    if (button->getIsPressed())
    {
        // generate the new colour
        newCol = {
            buttonCol.r * colCoeff,
            buttonCol.g * colCoeff,
            buttonCol.b * colCoeff
        };
    } else
    {
        // when it's not being pressed, set it back to the original colour
        newCol = buttonCol;
    }

    // set the button colour
    button->setCol(newCol);
    

    // The RenderWindow works with a raw SDL_Renderer. It's not intelligent & there's
    // no journaling, so the first thing that you draw will come out "underneath"
    // stuff that gets drawn later on. This also applies to the order in which you
    // add your components - first in will get drawn first & could get hidden by
    // other stuff.
    //
    // So, as we want our Button to appear underneath our cross, we should draw it first.
    // If it doesn't succeed for whatever reason, we should stop & return the error code.
    GOOEY_STATUS_CODE r = button->tick(event);
    if (r != GOOEY_SUCCESS) { return r; }
    

    // Now, let's draw our cross.
    // The RenderWindow provides some basic ways to draw to its pixels. You can draw lines,
    // and draw/fill triangles and rectangles. Soon you'll be able to set individual pixels,
    // or access the renderer itself for more customizable drawing. For now, we're going to
    // use RenderWindow::drawLine. There are a few overloads, but we'll take advantage of our
    // startPos, endPos, and lineCol variables to draw lines.
    // A pointer to the active RenderWindow is stored in ctx.

    // top left to bottom right - just startPos to endPos.
    ctx.renderWindow->drawLine(startPos, endPos, lineCol);
    
    // top right to bottom left - slightly more complicated; we need to swap either the x or y coords.
    // I'll swap the x.
    ctx.renderWindow->drawLine({endPos.x, startPos.y}, {startPos.x, endPos.y}, lineCol);

    // if we got this far, all must be well.
    return GOOEY_SUCCESS;

}