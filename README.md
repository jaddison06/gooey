# gooey

wx is old. qt is bloated. gtk is cringe.

gooey is *perfect*.

# what is gooey?

gooey is a ui toolkit for c++. Its platform abstraction is provided by libSDL, which I do not understand. SDL drives the RenderWindow class, a hacky mess of SO snippets. This black box, which exposes a friendly, inviting, and not at all questionable api, allows you to draw rectangles, lines, and even text! If you want, though, it's easier to just modify the pixels.

# how do I use gooey?

Gooey is based on a system of widgets (also called components). You can initialize these on the fly and pass them to an instance of the Gooey class, which represents your window. For more information, see main.cpp .

# how do I extend gooey?

Adding your own widgets is simple enough - they just need to extend Drawable, and define a tick() function. See graphics/widgets/MyWidget.cpp for more info.

# how do I install gooey?

Good question! I don't know anything about distributing cpp libraries, so you'll just have to download the source and hack it together! (: