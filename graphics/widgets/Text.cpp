#include "graphics/widgets/Text.h"

Text::Text(int x, int y, const char *text, Col col)
{
    this->x = x;
    this->y = y;
    this->text = text;
    this->col = col;
}

// it's ok to do this every frame
// because RenderWindow caches text textures.
GOOEY_STATUS_CODE Text::tick(SDL_Event *event)
{
    ctx.renderWindow->drawText(text, x, y, col);

    return GOOEY_SUCCESS;
}