#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <array>
#include "src/control/Tickable.h"
#include <math.h>
#include <unordered_map>

/*
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
*/

//#define BG_COL {175, 0, 255}
#define BG_COL {0, 0, 0}


struct Col
{
    int r, g, b;
};

struct coord2d
{
    int x, y;
};

struct textInfo
{
    SDL_Surface *textSurface;
    SDL_Texture *textTexture;
    SDL_Rect renderQuad;
};


// the RenderWindow handles cringy SDL stuff so I
// don't have to worry about it
//
// unfortunately it doesn't always do a great job

class RenderWindow: public Tickable
{
    public:
        RenderWindow(const char *title, const char *fontFile);
        ~RenderWindow();
        GOOEY_STATUS_CODE tick(SDL_Event *event);

        coord2d getWindowDimensions();

        // set border visibility
        void setWindowBorder(SDL_bool enable);

        // set fullscreen
        void setFullscreen(bool enable);

        void resizeWindow(int width, int height);

        // utility functions for drawing etc

        // draw line from startPos, at bearing, for length
        void drawLine(coord2d startPos, double bearing, int length, Col col);
        // draw line between startPos and endPos
        void drawLine(coord2d startPos, coord2d endPos, Col col);

        void drawTriangle(coord2d corners[3], Col col);
        // TODO: impl
        void fillTriangle(coord2d corners[3], Col col);

        void fillRect(coord2d pos, int w, int h, Col col);
        void fillRect(coord2d startPos, coord2d endPos, Col col);

        void drawText(const char *text, int x, int y, Col col, bool centered = false, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


    
    private:

        void init(const char *title, const char *fontFile);

        SDL_Window *win;
        SDL_Renderer *ren;

        std::unordered_map<const char *, textInfo> textBuffer;

        SDL_Texture *textTexture;
        TTF_Font *font;

        void freeTextTexture();
        void cleanup();

        int WIN_WIDTH, WIN_HEIGHT;

        double degToRad(double deg);

        void setRendererColour(Col *col);

        void logTTFError(std::ostream &os, const std::string &msg, bool quit = true);
        void logSDLError(std::ostream &os, const std::string &msg, bool quit = true, const char *error = NULL);

};