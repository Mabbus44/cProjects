#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "Constants.h"
class Map;

using namespace std;

class SDLWindow
{
  public:
    SDLWindow();
    virtual ~SDLWindow();
    virtual void open(int windowHeight=WINDOW_HEIGHT, int windowWidth=WINDOW_WIDTH);
    virtual void resizeWindow(int windowHeight, int windowWidth);
    void close();
    bool isOpen(){return _open;}
    bool requestClose = false;
  protected:
    SDL_Window* _window = NULL;
    SDL_Renderer* _renderer = NULL;
    SDL_Texture* _texture = NULL;
    bool _open = false;
};

class NeuronsWindow: public SDLWindow{
  public:
    NeuronsWindow(){};
    virtual ~NeuronsWindow(){};
    virtual void open(int windowHeight=WINDOW_HEIGHT, int windowWidth=WINDOW_WIDTH);
    virtual void resizeWindow(int windowHeight, int windowWidth);
    void drawClear();
    void setDrawColor(int r, int g, int b);
    void drawText(int x, int y, string text, SDL_Color c);
    void drawRect(int x, int y, int w, int h);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawNeuron(Map* m);
    void render();
  protected:
    TTF_Font* _font = NULL;
};

class MapWindow: public SDLWindow{
  public:
    MapWindow();
    virtual ~MapWindow();
    virtual void open(int windowHeight=WINDOW_HEIGHT, int windowWidth=WINDOW_WIDTH);
    virtual void resizeWindow(int windowHeight, int windowWidth);
    void drawPixel(int x, int y, int r, int g, int b);
    void renderPixels();
    void drawMap(Map* m);
  protected:
    uint8_t* _pixels;
};
#endif // SDLWINDOW_H
