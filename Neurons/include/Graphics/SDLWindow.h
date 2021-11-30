#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

using namespace std;

class SDLWindow
{
  public:
    SDLWindow();
    virtual ~SDLWindow();
    void drawPixel(int x, int y, int r, int g, int b);
    void renderPixels();
    void drawClear();
    void setDrawColor(int r, int g, int b);
    void drawText(int x, int y, string text);
    void drawRect(int x, int y, int w, int h);
    void drawLine(int x1, int x2, int y1, int y2);
    void render();
  private:
    SDL_Window* _window = NULL;
    SDL_Renderer* _renderer = NULL;
    SDL_Texture* _texture = NULL;
    TTF_Font* _font = NULL;
    uint8_t* _pixels;
};

#endif // SDLWINDOW_H
