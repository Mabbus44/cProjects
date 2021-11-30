#include "Graphics/SDLWindow.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Constants.h"

using namespace std;

SDLWindow::SDLWindow(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
  _window = SDL_CreateWindow( "SDL Graphics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
  if( _window == NULL )
    cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (_renderer == NULL)
    cout << "Unable to create renderer: " << SDL_GetError() << endl;
  SDL_RenderSetLogicalSize(_renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
  _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
  if (_texture == NULL)
    cout << "Unable to create texture: " << SDL_GetError() << endl;
  if( TTF_Init() == -1 )
    cout << "Warning: SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
  _font = TTF_OpenFont( "fonts/OpenSans-Regular.ttf", 20 );
  if( _font == NULL )
    cout << "Warning: Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
  _pixels = new uint8_t[WINDOW_WIDTH * WINDOW_HEIGHT * 4]();
  for(int i=0; i<WINDOW_WIDTH*WINDOW_HEIGHT; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

SDLWindow::~SDLWindow(){
  SDL_DestroyTexture(_texture);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
	SDL_Quit();
	delete[] _pixels;
}

void SDLWindow::renderPixels(){
  int texture_pitch = 0;
  void* texture_pixels = NULL;
  if (SDL_LockTexture(_texture, NULL, &texture_pixels, &texture_pitch) != 0) {
      cout << "Unable to lock texture: " << SDL_GetError() << endl;
  }
  else {
      memcpy(texture_pixels, _pixels, texture_pitch * WINDOW_HEIGHT);
  }
  SDL_UnlockTexture(_texture);

  SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
  SDL_RenderClear(_renderer);
  SDL_RenderCopy(_renderer, _texture, NULL, NULL);
  SDL_RenderPresent(_renderer);
  for(int i=0; i<WINDOW_WIDTH*WINDOW_HEIGHT; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
  }
}

void SDLWindow::drawText(int x, int y, string text){
  SDL_Surface* textSurface = TTF_RenderText_Solid( _font, text.c_str(), { 100, 100, 100 } );
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

void SDLWindow::drawClear(){
  SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
  SDL_RenderClear(_renderer);
}

void SDLWindow::drawRect(int x, int y, int w, int h){
  SDL_Rect fillRect = {x,y,w,h};
  SDL_RenderFillRect( _renderer, &fillRect );
}

void SDLWindow::drawLine(int x1, int x2, int y1, int y2){
  SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}

void SDLWindow::setDrawColor(int r, int g, int b){
  SDL_SetRenderDrawColor( _renderer, r, g, b, 0xFF );
}

void SDLWindow::render(){
  SDL_RenderPresent(_renderer);
}

void SDLWindow::drawPixel(int x, int y, int r, int g, int b){
  _pixels[(2*x+2*y*WINDOW_WIDTH)*4] = r;
  _pixels[(2*x+1+2*y*WINDOW_WIDTH)*4] = r;
  _pixels[(2*x+(2*y+1)*WINDOW_WIDTH)*4] = r;
  _pixels[(2*x+1+(2*y+1)*WINDOW_WIDTH)*4] = r;
  _pixels[(2*x+2*y*WINDOW_WIDTH)*4+1] = g;
  _pixels[(2*x+1+2*y*WINDOW_WIDTH)*4+1] = g;
  _pixels[(2*x+(2*y+1)*WINDOW_WIDTH)*4+1] = g;
  _pixels[(2*x+1+(2*y+1)*WINDOW_WIDTH)*4+1] = g;
  _pixels[(2*x+2*y*WINDOW_WIDTH)*4+2] = b;
  _pixels[(2*x+1+2*y*WINDOW_WIDTH)*4+2] = b;
  _pixels[(2*x+(2*y+1)*WINDOW_WIDTH)*4+2] = b;
  _pixels[(2*x+1+(2*y+1)*WINDOW_WIDTH)*4+2] = b;
}
