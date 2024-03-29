#include "Graphics/SDLWindow.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Map.h"

using namespace std;

SDLWindow::SDLWindow(){
}

SDLWindow::~SDLWindow(){
	if(_open)
    close();
}

void SDLWindow::open(int windowHeight, int windowWidth){
  if(_open)
    return;
  this->_windowHeight = windowHeight;
  this->_windowWidth = windowWidth;
	_open = true;
  _window = SDL_CreateWindow( "SDL Graphics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if( _window == NULL )
    cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
  windowId = SDL_GetWindowID(_window);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (_renderer == NULL)
    cout << "Unable to create renderer: " << SDL_GetError() << endl;
  SDL_RenderSetLogicalSize(_renderer, windowWidth, windowHeight);
  _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
  if (_texture == NULL)
    cout << "Unable to create texture: " << SDL_GetError() << endl;
}

void SDLWindow::resizeWindow(int windowHeight, int windowWidth){
  cout << "SDLWindow::resizeWindow(" << windowHeight << ", " << windowWidth << ")" << endl;
  this->_windowHeight = windowHeight;
  this->_windowWidth = windowWidth;
  SDL_DestroyTexture(_texture);
  SDL_DestroyRenderer(_renderer);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (_renderer == NULL)
    cout << "Unable to create renderer: " << SDL_GetError() << endl;
  SDL_RenderSetLogicalSize(_renderer, windowWidth, windowHeight);
  _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
  if (_texture == NULL)
    cout << "Unable to create texture: " << SDL_GetError() << endl;
}

void SDLWindow::close(){
  SDL_DestroyTexture(_texture);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  keyFocus = false;
  _open = false;
}

void NeuronsWindow::open(int windowHeight, int windowWidth){
  SDLWindow::open(windowHeight, windowWidth);
  _font = TTF_OpenFont( "fonts/OpenSans-Regular.ttf", 25 );
  if( _font == NULL )
    cout << "Warning: Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
  _smallFont = TTF_OpenFont( "fonts/OpenSans-Regular.ttf", 15 );
  if( _smallFont == NULL )
    cout << "Warning: Failed to load small lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
}

void NeuronsWindow::close(){
  if(_open){
    TTF_CloseFont(_font);
    TTF_CloseFont(_smallFont);
    SDLWindow::close();
  }
}

void NeuronsWindow::resizeWindow(int windowHeight, int windowWidth){
  SDLWindow::resizeWindow(windowHeight, windowWidth);
}

void NeuronsWindow::setDrawColor(int r, int g, int b){
  SDL_SetRenderDrawColor( _renderer, r, g, b, 0xFF );
}

void NeuronsWindow::drawRect(int x, int y, int w, int h){
  SDL_Rect fillRect = {x,y,w,h};
  SDL_RenderFillRect( _renderer, &fillRect );
}

void NeuronsWindow::drawLine(int x1, int y1, int x2, int y2){
  SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}

void NeuronsWindow::drawText(int x, int y, string text, SDL_Color c, int fontSize){
  SDL_Surface* textSurface;
  if(fontSize==20)
    textSurface=TTF_RenderText_Solid( _font, text.c_str(),  c);
  else
    textSurface=TTF_RenderText_Solid( _smallFont, text.c_str(),  c);
  if( textSurface == NULL ){
    cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
    return;
  }
  SDL_Texture* mTexture = SDL_CreateTextureFromSurface( _renderer, textSurface );
  if( mTexture == NULL ){
    cout <<"Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
    return;
  }
  int mWidth = textSurface->w;
  int mHeight = textSurface->h;
  SDL_Rect rect = {x, y, mWidth, mHeight};
  SDL_RenderCopy(_renderer, mTexture, NULL, &rect);
  SDL_FreeSurface( textSurface );
  SDL_DestroyTexture( mTexture );
}

void NeuronsWindow::prepareRender(){
  SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
  drawText(10,10, "Not implemented", {0xFF, 0x00, 0x00});
}

void NeuronsWindow::render(){
  SDL_RenderPresent(_renderer);
}

MapWindow::MapWindow(){
  cout << "MapWindow::MapWindow()" << endl;
}

MapWindow::~MapWindow(){
  cout << "MapWindow::~MapWindow()" << endl;
  if(_open)
    delete[] _pixels;
}

void MapWindow::open(int windowHeight, int windowWidth){
  cout << "MapWindow::open()" << endl;
	if(_open)
    return;
	SDLWindow::open(windowHeight, windowWidth);
  _pixels = new uint8_t[windowWidth * windowHeight * 4];
  cout << "Allocated " << windowWidth * windowHeight * 4 << " pixels" << endl;
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

void MapWindow::close(){
  cout << "MapWindow::close()" << endl;
  if(_open){
    // TODO unpause map
    delete[] _pixels;
    SDLWindow::close();
  }
}

void MapWindow::resizeWindow(int windowHeight, int windowWidth){
	SDLWindow::resizeWindow(windowHeight, windowWidth);
  delete [] _pixels;
  _pixels = new uint8_t[windowWidth * windowHeight * 4];
  cout << "Allocated " << windowWidth * windowHeight * 4 << " pixels" << endl;
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0x00;
    _pixels[i*4+1] = 0x00;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

void MapWindow::prepareRender(){
  //cout << "MapWindow::prepareRender(" << _windowWidth << ", " << _windowHeight << ")" << endl;
  if(mapRef == nullptr){
    cout << "No mapref" << endl;
    return;
  }
  for(int i=0; i<_windowWidth*_windowHeight; i++){
    _pixels[i*4] = 0x33;
    _pixels[i*4+1] = 0x33;
    _pixels[i*4+2] = 0x33;
  }
  //mapRef->draw(this, selectedEntityType, selectedEntityId);
  if(_windowHeight > 100 && _windowWidth > 100){
    _debugInt++;
    _debugInt = _debugInt % 20;
    for(int x=10; x<20; x++){
      for(int y=10; y<20; y++){
        _pixels[(2*(x+_debugInt)+2*y*_windowWidth)*4] = 255;
        _pixels[(2*(x+_debugInt)+2*y*_windowWidth)*4+1] = 0;
        _pixels[(2*(x+_debugInt)+2*y*_windowWidth)*4+2] = 0;
      }
    }
  }
  int texture_pitch = 0;
  void* texture_pixels = NULL;
  if (SDL_LockTexture(_texture, NULL, &texture_pixels, &texture_pitch) != 0) {
    cout << "Unable to lock texture: " << SDL_GetError() << endl;
  }
  else {
    memcpy(texture_pixels, _pixels, texture_pitch * _windowHeight);
    cout << "texture_pixels " << texture_pixels << endl;
  }
  SDL_UnlockTexture(_texture);
  SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
  SDL_RenderClear(_renderer);
  SDL_RenderCopy(_renderer, _texture, NULL, NULL);
}

void MapWindow::render(){
  //cout << "MapWindow::render()" << endl;
  SDL_RenderPresent(_renderer);
}

void MapWindow::drawPixel(int x, int y, int r, int g, int b, bool selected){
  if(x<0 || x>=_windowWidth/2 || y<0 || y>=_windowHeight/2)
    return;

  _pixels[(2*x+2*y*_windowWidth)*4] = r;
  _pixels[(2*x+1+2*y*_windowWidth)*4] = r;
  _pixels[(2*x+(2*y+1)*_windowWidth)*4] = r;
  _pixels[(2*x+1+(2*y+1)*_windowWidth)*4] = r;
  _pixels[(2*x+2*y*_windowWidth)*4+1] = g;
  _pixels[(2*x+1+2*y*_windowWidth)*4+1] = g;
  _pixels[(2*x+(2*y+1)*_windowWidth)*4+1] = g;
  _pixels[(2*x+1+(2*y+1)*_windowWidth)*4+1] = g;
  _pixels[(2*x+2*y*_windowWidth)*4+2] = b;
  _pixels[(2*x+1+2*y*_windowWidth)*4+2] = b;
  _pixels[(2*x+(2*y+1)*_windowWidth)*4+2] = b;
  _pixels[(2*x+1+(2*y+1)*_windowWidth)*4+2] = b;
  if(selected){
    if(x>0){
      if(y>0){
        _pixels[(2*x-1+(2*y-1)*_windowWidth)*4] = r;
        _pixels[(2*x-1+(2*y-1)*_windowWidth)*4+1] = g;
        _pixels[(2*x-1+(2*y-1)*_windowWidth)*4+2] = b;
      }
      _pixels[(2*x-1+(2*y)*_windowWidth)*4] = r;
      _pixels[(2*x-1+(2*y)*_windowWidth)*4+1] = g;
      _pixels[(2*x-1+(2*y)*_windowWidth)*4+2] = b;
      _pixels[(2*x-1+(2*y+1)*_windowWidth)*4] = r;
      _pixels[(2*x-1+(2*y+1)*_windowWidth)*4+1] = g;
      _pixels[(2*x-1+(2*y+1)*_windowWidth)*4+2] = b;
      if(y<(_windowHeight/2-1)){
        _pixels[(2*x-1+(2*y+2)*_windowWidth)*4] = r;
        _pixels[(2*x-1+(2*y+2)*_windowWidth)*4+1] = g;
        _pixels[(2*x-1+(2*y+2)*_windowWidth)*4+2] = b;
      }
    }
    if(y>0){
      _pixels[(2*x+(2*y-1)*_windowWidth)*4] = r;
      _pixels[(2*x+(2*y-1)*_windowWidth)*4+1] = g;
      _pixels[(2*x+(2*y-1)*_windowWidth)*4+2] = b;
      _pixels[(2*x+1+(2*y-1)*_windowWidth)*4] = r;
      _pixels[(2*x+1+(2*y-1)*_windowWidth)*4+1] = g;
      _pixels[(2*x+1+(2*y-1)*_windowWidth)*4+2] = b;
    }
    if(x<(_windowWidth/2-1)){
      if(y>0){
        _pixels[(2*x+2+(2*y-1)*_windowWidth)*4] = r;
        _pixels[(2*x+2+(2*y-1)*_windowWidth)*4+1] = g;
        _pixels[(2*x+2+(2*y-1)*_windowWidth)*4+2] = b;
      }
      _pixels[(2*x+2+(2*y)*_windowWidth)*4] = r;
      _pixels[(2*x+2+(2*y)*_windowWidth)*4+1] = g;
      _pixels[(2*x+2+(2*y)*_windowWidth)*4+2] = b;
      _pixels[(2*x+2+(2*y+1)*_windowWidth)*4] = r;
      _pixels[(2*x+2+(2*y+1)*_windowWidth)*4+1] = g;
      _pixels[(2*x+2+(2*y+1)*_windowWidth)*4+2] = b;
      if(y<(_windowHeight/2-1)){
        _pixels[(2*x+2+(2*y+2)*_windowWidth)*4] = r;
        _pixels[(2*x+2+(2*y+2)*_windowWidth)*4+1] = g;
        _pixels[(2*x+2+(2*y+2)*_windowWidth)*4+2] = b;
      }
    }
    if(y<(_windowHeight/2-1)){
      _pixels[(2*x+(2*y+2)*_windowWidth)*4] = r;
      _pixels[(2*x+(2*y+2)*_windowWidth)*4+1] = g;
      _pixels[(2*x+(2*y+2)*_windowWidth)*4+2] = b;
      _pixels[(2*x+1+(2*y+2)*_windowWidth)*4] = r;
      _pixels[(2*x+1+(2*y+2)*_windowWidth)*4+1] = g;
      _pixels[(2*x+1+(2*y+2)*_windowWidth)*4+2] = b;
    }
  }
}

