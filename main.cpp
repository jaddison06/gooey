// Small tutorial on using Gooey.

// Gooey includes
#include "control/Gooey.h"
#include "control/CallbackAccepter.h"

// Widgets we're going to use
#include "graphics/widgets/Button.h"
#include "graphics/widgets/Text.h"
#include "graphics/widgets/MyWidget.h"

// demo of Gooey's vast capability

// a Gooey app should extend CallbackAccepter - you'll see why in a bit
class GooeyDemo : public CallbackAccepter
{
    public:
        GooeyDemo()
        {
            // initialize Gooey with window title, file for fonts, and a pointer to your app.
            // if you use new, remember to delete!
            gooey = new Gooey("Demo", "res/Montserrat-Regular.otf", this);

            // add some widgets to our app. we don't need to worry about deleting these - the window manager
            // does it automatically. This also means we can store the pointers if we want to communicate with
            // the widgets later on.

            // you'd normally just put these into the constructor but here they are for the sake of transparency
            int buttonX = gooey->getWindowDimensions().x - 55;
            int buttonY = 30;
            int buttonSize = 25;
            Col buttonCol = {255, 0, 0};
            const char *buttonName = "quitBtn";
            // all will be revealed soon! just you wait
            CallbackAccepter *buttonParent = this;

            gooey->addComponent(new Button(buttonX, buttonY, buttonSize, buttonSize, buttonCol, buttonName, buttonParent));

            // this is a more standard way of doing it
            gooey->addComponent(new Text(50, 50, "hello world", {255, 255, 0}));

            // A button with a cross in it - for more information on custom widgets, take a look at graphics/widgets/MyWidget.cpp
            gooey->addComponent(new MyWidget(50, 150, {255, 0, 175}, {0, 0, 0}, "pinkButton", this));
        }

        // Gooey will take care of _literally_ everything else.
        ~GooeyDemo()
        {
            delete gooey;
        }

        // the moment you've been waiting for!
        // A CallbackAccepter can take callbacks from various places. Each callback includes
        // a string to identify the sender, and an SDL_Event which describes what's going on
        // (although sometimes you won't need the event)
        //
        // Widgets, for example our quit button, can send us callbacks - remember we gave it
        // a pointer to its parent, and a name.
        //
        // Gooey will also send us callbacks each time it renders a frame - the component name
        // will be "gooey". Here we can do any additional processing that we want - you might 
        // update a game state, or do some i/o. Technically, this happens _before_ the frame
        // actually gets rendered.
        void doCallback(std::string componentName, SDL_Event *event)
        {
            if (
                componentName == "gooey" &&          // if Gooey sends us an event,
                event->type == SDL_KEYDOWN &&        // and it's a keypress
                event->key.keysym.sym == SDLK_ESCAPE // of the "Escape" key,
            )
            {
                printf("Escape pressed, quitting!\n");               // then quit.

                // Gooey won't quit immediately - it'll finish processing & rendering this frame,
                // and on the next cycle it'll see this & exit.
                gooey->quit();
            }

            // if the quit button sends us a callback, it's been pressed.
            // we don't need to check the event because we already know
            // that this means a quit.
            if (componentName == "quitBtn")
            {
                printf("Red button pressed, quitting!\n");
                gooey->quit();
            }

            // if the pink MyWidget sends us a callback, say hello!
            if (componentName == "pinkButton")
            {
                printf("Hello, World!\n");
            }
        }

        // this is cool! Gooey's start() method returns a GOOEY_STATUS_CODE enum.
        // If we want to quit normally - as opposed to from an error - this will
        // be GOOEY_QUIT, which is equal to 0. This means you can just return it from main().
        int start()
        {
            // this will block until something tells the app to quit
            int r = gooey->start();
            return r;
        }
    
    private:
        // our Gooey instance
        Gooey *gooey;
};

// entrypoint for our program. simply initializes a GooeyDemo and runs it.
int main()
{
    auto demo = GooeyDemo();
    // our GOOEY_STATUS_CODE, as an int
    return demo.start();
}