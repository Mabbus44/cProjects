#include "Graphics/SDLWindow.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Map.h"

using namespace std;

SDLWindow::SDLWindow(){
  _pixels = new uint8_t[WINDOW_WIDTH * WINDOW_HEIGHT * 4];
}

SDLWindow::~SDLWindow(){
	if(_open)
    close();
	delete[] _pixels;
}

void NeuronsWindow::open(int windowHeight, int windowWidth){
	_open = true;
  _window = SDL_CreateWindow( "SDL Graphics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if( _window == NULL )
    cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (_renderer == NULL)
    cout << "Unable to create renderer: " << SDL_GetError() << endl;
  SDL_RenderSetLogicalSize(_renderer, windowWidth, windowHeight);
  _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
  if (_texture == NULL)
    cout << "Unable to create texture: " << SDL_GetError() << endl;
  _font = TTF_OpenFont( "fonts/OpenSans-Regular.ttf", 20 );
  if( _font == NULL )
    cout << "Warning: Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

void MapWindow::open(int windowHeight, int windowWidth){
	_open = true;
  _window = SDL_CreateWindow( "SDL Graphics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if( _window == NULL )
    cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (_renderer == NULL)
    cout << "Unable to create renderer: " << SDL_GetError() << endl;
  SDL_RenderSetLogicalSize(_renderer, windowWidth, windowHeight);
  _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
  if (_texture == NULL)
    cout << "Unable to create texture: " << SDL_GetError() << endl;
  _font = TTF_OpenFont( "fonts/OpenSans-Regular.ttf", 20 );
  if( _font == NULL )
    cout << "Warning: Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

void SDLWindow::close(){
  SDL_DestroyTexture(_texture);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
	requestClose = false;
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

void SDLWindow::drawText(int x, int y, string text, SDL_Color c){
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

void SDLWindow::drawClear(){
  SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
  SDL_RenderClear(_renderer);
}

void SDLWindow::drawRect(int x, int y, int w, int h){
  SDL_Rect fillRect = {x,y,w,h};
  SDL_RenderFillRect( _renderer, &fillRect );
}

void SDLWindow::drawLine(int x1, int y1, int x2, int y2){
  SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}

void SDLWindow::setDrawColor(int r, int g, int b){
  SDL_SetRenderDrawColor( _renderer, r, g, b, 0xFF );
}

void SDLWindow::render(){
  SDL_RenderPresent(_renderer);
}

void SDLWindow::drawPixel(int x, int y, int r, int g, int b){
  if(x<0 || x>=WINDOW_WIDTH/2 || y<0 || y>=WINDOW_HEIGHT/2)
    return;

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

void SDLWindow::drawMap(Map* m){
  m->mapDrawnBy = this;
  m->allowDrawMap = false;
  open();
  SDL_Event e;
  SDL_PollEvent(&e);
  while(e.type != SDL_QUIT && e.type != SDL_KEYDOWN && requestClose != true){
    SDL_PollEvent(&e);
    if((m->runningLogic && m->allowDrawMap) || !m->runningLogic){
      m->draw(this);
      m->allowDrawMap = false;
    }
  }
  close();
  m->mapDrawnBy = NULL;
}

void SDLWindow::drawNeuron(Map* m){
  m->neuronsDrawnBy = this;
  m->allowDrawNeurons = false;
  int animalType = CARNIVORE_NEURON;
  int animalIndex = m->carnivores().size();
  open();
  SDL_Event e;
  SDL_PollEvent(&e);
  while(e.type != SDL_QUIT && (e.type != SDL_KEYDOWN || e.key.keysym.sym != SDLK_ESCAPE) && requestClose != true){
    if((m->runningLogic && m->allowDrawNeurons) || !m->runningLogic){
      if(m->carnivores().size()>0 || m->herbivores().size()>0){
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym != SDLK_TAB)
          animalIndex++;
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym != SDLK_LSHIFT)
          animalIndex--;
        switch(animalType){
          case HERBIVORE_NEURON:
            if(animalIndex >= (int)m->herbivores().size()){
              if(m->carnivores().size()>0)
                animalType = CARNIVORE_NEURON;
              animalIndex=0;
            }
            if(animalIndex < 0){
              if(m->carnivores().size()>0){
                animalType = CARNIVORE_NEURON;
                animalIndex=m->carnivores().size()-1;
              }else
                animalIndex=m->herbivores().size()-1;
            }
            break;
          case CARNIVORE_NEURON:
            if(animalIndex >= (int)m->carnivores().size()){
              if(m->herbivores().size()>0)
                animalType = HERBIVORE_NEURON;
              animalIndex=0;
            }
            if(animalIndex < 0){
              if(m->herbivores().size()>0){
                animalType = HERBIVORE_NEURON;
                animalIndex=m->herbivores().size()-1;
              }else
                animalIndex=m->carnivores().size()-1;
            }
            break;
        }
        switch(animalType){
          case HERBIVORE_NEURON:
            m->herbivores()[animalIndex]->drawNeurons(this);
            break;
          case CARNIVORE_NEURON:
            m->carnivores()[animalIndex]->drawNeurons(this);
            break;
        }
      }
      m->allowDrawNeurons = false;
    }
    SDL_PollEvent(&e);
  }
  close();
  m->neuronsDrawnBy = NULL;
}
