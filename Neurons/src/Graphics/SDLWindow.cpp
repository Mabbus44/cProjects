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
  this->windowHeight = windowHeight;
  this->windowWidth = windowWidth;
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
  this->windowHeight = windowHeight;
  this->windowWidth = windowWidth;
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
  _font = TTF_OpenFont( "fonts/OpenSans-Regular.ttf", 20 );
  if( _font == NULL )
    cout << "Warning: Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
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

void NeuronsWindow::drawText(int x, int y, string text, SDL_Color c){
  SDL_Surface* textSurface = TTF_RenderText_Solid( _font, text.c_str(),  c);
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

void NeuronsWindow::changeAnimal(bool add){
  if(add)
    animalIndex++;
  else
    animalIndex--;
  int animalCount;
  switch(animalType){
    case HERBIVORE_NEURON:
      animalCount = mapRef->herbivores().size();
      break;
    case CARNIVORE_NEURON:
      animalCount = mapRef->carnivores().size();
      break;
    case BEST_HERBIVORE_NEURON:
      animalCount = mapRef->bestHerbivores().size();
      break;
    case BEST_CARNIVORE_NEURON:
      animalCount = mapRef->bestCarnivores().size();
      break;
  }
  if(animalIndex>=animalCount)
    animalIndex = 0;
  if(animalIndex<0)
    animalIndex = animalCount-1;
}

void NeuronsWindow::changeAnimalType(bool add){
  animalIndex = 0;
  if(add)
    animalType++;
  else
    animalType--;
  if(animalType<0)
    animalType = DRAW_NEURON_TYPE_COUNT-1;
  if(animalType>=DRAW_NEURON_TYPE_COUNT)
    animalType = 0;
}

void NeuronsWindow::prepareRender(){
  SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
  SDL_RenderClear(_renderer);
  switch(animalType){
    case HERBIVORE_NEURON:
      if(animalIndex>=0 && animalIndex<(int)mapRef->herbivores().size())
        mapRef->herbivores()[animalIndex]->drawNeurons(this);
      else
        drawText(10,10, "No herbivores on map", {0xFF, 0x00, 0x00});
      break;
    case CARNIVORE_NEURON:
      if(animalIndex>=0 && animalIndex<(int)mapRef->carnivores().size())
        mapRef->carnivores()[animalIndex]->drawNeurons(this);
      else
        drawText(10,10, "No carnivores on map", {0xFF, 0x00, 0x00});
      break;
    case BEST_HERBIVORE_NEURON:
      if(animalIndex>=0 && animalIndex<(int)mapRef->bestHerbivores().size())
        mapRef->bestHerbivores()[animalIndex]->drawNeurons(this);
      else
        drawText(10,10, "No best herbivores on map", {0xFF, 0x00, 0x00});
      break;
    case BEST_CARNIVORE_NEURON:
      if(animalIndex>=0 && animalIndex<(int)mapRef->bestCarnivores().size())
        mapRef->bestCarnivores()[animalIndex]->drawNeurons(this);
      else
        drawText(10,10, "No best carnivores on map", {0xFF, 0x00, 0x00});
      break;
  }
}

void NeuronsWindow::render(){
  SDL_RenderPresent(_renderer);
}

MapWindow::MapWindow(){
}

MapWindow::~MapWindow(){
  if(_open)
    delete[] _pixels;
}

void MapWindow::open(int windowHeight, int windowWidth){
	if(_open)
    return;
	SDLWindow::open(windowHeight, windowWidth);
  _pixels = new uint8_t[windowWidth * windowHeight * 4];
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

void MapWindow::close(){
  if(_open){
    mapRef->pause = false;
    delete[] _pixels;
    SDLWindow::close();
  }
}

void MapWindow::resizeWindow(int windowHeight, int windowWidth){
	SDLWindow::resizeWindow(windowHeight, windowWidth);
  delete [] _pixels;
  _pixels = new uint8_t[windowWidth * windowHeight * 4];
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

void MapWindow::prepareRender(){
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
  }
  mapRef->draw(this);
  int texture_pitch = 0;
  void* texture_pixels = NULL;
  if (SDL_LockTexture(_texture, NULL, &texture_pixels, &texture_pitch) != 0) {
      cout << "Unable to lock texture: " << SDL_GetError() << endl;
  }
  else {
      memcpy(texture_pixels, _pixels, texture_pitch * windowHeight);
  }
  SDL_UnlockTexture(_texture);
  SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
  SDL_RenderClear(_renderer);
  SDL_RenderCopy(_renderer, _texture, NULL, NULL);
}

void MapWindow::render(){
  SDL_RenderPresent(_renderer);
}

void MapWindow::drawPixel(int x, int y, int r, int g, int b){
  if(x<0 || x>=windowWidth/2 || y<0 || y>=windowHeight/2)
    return;

  _pixels[(2*x+2*y*windowWidth)*4] = r;
  _pixels[(2*x+1+2*y*windowWidth)*4] = r;
  _pixels[(2*x+(2*y+1)*windowWidth)*4] = r;
  _pixels[(2*x+1+(2*y+1)*windowWidth)*4] = r;
  _pixels[(2*x+2*y*windowWidth)*4+1] = g;
  _pixels[(2*x+1+2*y*windowWidth)*4+1] = g;
  _pixels[(2*x+(2*y+1)*windowWidth)*4+1] = g;
  _pixels[(2*x+1+(2*y+1)*windowWidth)*4+1] = g;
  _pixels[(2*x+2*y*windowWidth)*4+2] = b;
  _pixels[(2*x+1+2*y*windowWidth)*4+2] = b;
  _pixels[(2*x+(2*y+1)*windowWidth)*4+2] = b;
  _pixels[(2*x+1+(2*y+1)*windowWidth)*4+2] = b;
}

