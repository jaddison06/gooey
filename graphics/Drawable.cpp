#include "graphics/Drawable.h"

void Drawable::drawableInit(DrawableContext ctx)
{
    this->ctx = ctx;
    afterInit();
}