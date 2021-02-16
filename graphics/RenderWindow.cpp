#include "RenderWindow.h"

RenderWindow::RenderWindow(const char *title, const char *fontFile)
{
	init(title, fontFile);
}

void RenderWindow::init(const char *title, const char *fontFile)
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        logSDLError(std::cout, "SDL_Init", false);
    }

    if( TTF_Init() != 0 )
    {
        logTTFError(std::cout, "TTF_Init", false);
    }

    font = TTF_OpenFont(fontFile, 15);
    if (font == NULL)
    {
        logTTFError(std::cout, "TTF_OpenFont");
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    WIN_WIDTH = DM.w;
    WIN_HEIGHT = DM.h;

    WIN_WIDTH = 500;
    WIN_HEIGHT = 500;

    win = SDL_CreateWindow(title, 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (win == NULL)
    {
        logSDLError(std::cout, "SDL_CreateWindow");
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
    {
        SDL_DestroyWindow(win);
        logSDLError(std::cout, "SDL_CreateRenderer");
    }
    
    textTexture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT);
    if (textTexture == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        logSDLError(std::cout, "SDL_CreateTexture");
    }

}

void RenderWindow::resizeWindow(int width, int height)
{
    //printf("Resizing to %ix%i\n", width, height);
    WIN_WIDTH = width;
    WIN_HEIGHT = height;
}

coord2d RenderWindow::getWindowDimensions()
{
    return { WIN_WIDTH, WIN_HEIGHT };
}

void RenderWindow::setWindowBorder(SDL_bool enable)
{
    SDL_SetWindowBordered(win, enable);
}

void RenderWindow::setFullscreen(bool enable)
{
    if (enable)
    {
        SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
    } else
    {
        SDL_SetWindowFullscreen(win, 0);
    }

}

void RenderWindow::cleanup()
{
    // SDL & TTF cleanup

    //SDL_DestroyTexture(tex);
    freeTextTexture();

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

RenderWindow::~RenderWindow()
{
    cleanup();
    SDL_Quit();
}


void RenderWindow::setRendererColour(Col *col)
{
    if (col == NULL)
    {
        Col col_temp = BG_COL;
        col = &col_temp;
    }
    SDL_SetRenderDrawColor(ren, col->r, col->g, col->b, SDL_ALPHA_OPAQUE);

}

void RenderWindow::drawLine(coord2d startPos, double bearing, int length, Col col)
{
    coord2d endPos = startPos;

    endPos.x += length * cos(degToRad(bearing));
    endPos.y += length * sin(degToRad(bearing));

    drawLine(startPos, endPos, col);

}

void RenderWindow::drawLine(coord2d startPos, coord2d endPos, Col col)
{
    setRendererColour(&col);
    SDL_RenderDrawLine(ren, startPos.x, startPos.y, endPos.x, endPos.y);
}

void RenderWindow::drawTriangle(coord2d corners[3], Col col)
{
    drawLine(corners[0], corners[1], col);
    drawLine(corners[1], corners[2], col);
    drawLine(corners[2], corners[0], col);
}

void RenderWindow::fillTriangle(coord2d corners[3], Col col)
{
    // clever things go here !!
}


void RenderWindow::fillRect(coord2d pos, int w, int h, Col col)
{
    //printf("Filling rect\nRenderer is at %p\n", ren);

    SDL_Rect rect;
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = w;
    rect.h = h;

    setRendererColour(&col);
    SDL_RenderFillRect(ren, &rect);

}

void RenderWindow::fillRect(coord2d startPos, coord2d endPos, Col col)
{
    fillRect(startPos, endPos.x - startPos.x, endPos.y - startPos.y, col);
}


void RenderWindow::freeTextTexture()
{
    if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
    }
}

// TODO: textTexture held a pointer to the buffer item, so freeing it _kept the item in the buffer_ as a nullptr.
// this meant that we didn't decide to re-create it, instead we tried to render the nullptr, which obviously came up blank.
// so we need to copy the texture from the buffer into textTexture.
// (also probably free stuff from the buffer - mem leak otherwise!)
void RenderWindow::drawText(const char *text, int x, int y, Col col, bool centered, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    freeTextTexture();

    //printf("%s\n", text);

    SDL_Rect renderQuad;
/*
    // check if we've seen this string before
    if (textBuffer.find(text) == textBuffer.end())
    {
*/
        //printf("not seen before\n");

        SDL_Surface *textSurface = TTF_RenderText_Solid( font, text, {col.r, col.g, col.b, SDL_ALPHA_OPAQUE} );
        textTexture = SDL_CreateTextureFromSurface( ren, textSurface );
        
        // finalX needs to be at the top left
        int finalX;
        if (centered)
        {
            finalX = x - (textSurface->w / 2);
        } else
        {
            finalX = x;
        }
        renderQuad = {finalX, y, textSurface->w, textSurface->h};

        if( clip != NULL )
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        textBuffer[text] = {
            textSurface,
            textTexture,
            renderQuad
        };
    //}

    //printf("finding\n");

    textTexture = textBuffer[text].textTexture;
    renderQuad = textBuffer[text].renderQuad;

    //printf("rendering\n");

    SDL_RenderCopyEx( ren, textTexture, clip, &renderQuad, angle, center, flip );

}


double RenderWindow::degToRad(double deg)
{
    return (deg * M_PI) / 180;
}

void RenderWindow::logTTFError(std::ostream &os, const std::string &msg, bool quit)
{
    if (quit)
    {
        TTF_Quit();
    }

    logSDLError(os, msg, quit, TTF_GetError());
}

void RenderWindow::logSDLError(std::ostream &os, const std::string &msg, bool quit, const char *error)
{
    if (error == NULL)
    {
        error = SDL_GetError();
    }

	os << msg << " error: " << error << std::endl;
    if (quit)
    {
        SDL_Quit();
    }
}

GOOEY_STATUS_CODE RenderWindow::tick(SDL_Event *event)
{
    SDL_RenderPresent(ren);

    setRendererColour(NULL);
/*
    std::string temp;
    getline(std::cin, temp);*/
    SDL_RenderClear(ren);
    return GOOEY_SUCCESS;
}