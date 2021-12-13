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
}

void SDLWindow::resizeWindow(int windowHeight, int windowWidth){
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
	requestClose = false;
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

void NeuronsWindow::drawClear(){
  SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
  SDL_RenderClear(_renderer);
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

void NeuronsWindow::drawNeuron(Map* m){
  m->neuronsDrawnBy = this;
  m->allowDrawNeurons = false;
  int animalType = HERBIVORE_NEURON;
  int animalIndex = m->carnivores().size()-1;
  open();
  SDL_Event e;
  SDL_PollEvent(&e);
  while(e.type != SDL_QUIT && (e.type != SDL_KEYDOWN || e.key.keysym.sym != SDLK_ESCAPE) && requestClose != true){
    if(e.type == SDL_KEYDOWN){
      //cout << "Key " << e.key.keysym.sym << " neurons" << endl;
      if(e.key.keysym.sym == SDLK_w)
        animalIndex++;
      if(e.key.keysym.sym == SDLK_e)
        animalIndex--;
      if(e.key.keysym.sym == SDLK_q){
        animalType++;
      }
    }
    //if(e.type == SDL_WINDOWEVENT && e.window.event==SDL_WINDOWEVENT_SIZE_CHANGED)
      //cout << "Window " << (int)e.window.windowID << " neurons" << endl;
    if(e.type == SDL_WINDOWEVENT){
      if(e.window.event==SDL_WINDOWEVENT_SIZE_CHANGED){
        //cout << e.window.windowID << endl;
        //cout << "windows reeeeeeeeeesized" << endl;
        //resizeWindow(e.window.data2, e.window.data1);
      }
    }
    if((m->runningLogic && m->allowDrawNeurons) || !m->runningLogic){
      int animalCount = 0;
      if(animalType >= DRAW_NEURON_TYPE_COUNT)
        animalType = 0;
      switch(animalType){
        case HERBIVORE_NEURON: animalCount = m->herbivores().size(); break;
        case CARNIVORE_NEURON: animalCount = m->carnivores().size(); break;
        case BEST_HERBIVORE_NEURON: animalCount = m->bestHerbivores().size(); break;
        case BEST_CARNIVORE_NEURON: animalCount = m->bestCarnivores().size(); break;
      }
      if(animalIndex >= animalCount)
        animalIndex=0;
      if(animalIndex < 0)
        animalIndex=animalCount-1;
      switch(animalType){
        case HERBIVORE_NEURON:
          if(animalCount>0)
            m->herbivores()[animalIndex]->drawNeurons(this);
          else{
            drawClear();
            drawText(10,10, "No herbivores on map", {0xFF, 0x00, 0x00});
            render();
          }
          break;
        case CARNIVORE_NEURON:
          if(animalCount>0)
            m->carnivores()[animalIndex]->drawNeurons(this);
          else{
            drawClear();
            drawText(10,10, "No carnivores on map", {0xFF, 0x00, 0x00});
            render();
          }
          break;
        case BEST_HERBIVORE_NEURON:
          if(animalCount>0)
            m->bestHerbivores()[animalIndex]->drawNeurons(this);
          else{
            drawClear();
            drawText(10,10, "No best herbivores on map", {0xFF, 0x00, 0x00});
            render();
          }
          break;
        case BEST_CARNIVORE_NEURON:
          if(animalCount>0)
            m->bestCarnivores()[animalIndex]->drawNeurons(this);
          else{
            drawClear();
            drawText(10,10, "No best carnivores on map", {0xFF, 0x00, 0x00});
            render();
          }
          break;
      }
    }
    m->allowDrawNeurons = false;
    SDL_PollEvent(&e);
  }
  close();
  m->neuronsDrawnBy = NULL;
}

void NeuronsWindow::render(){
  SDL_RenderPresent(_renderer);
}

MapWindow::MapWindow(){
  _pixels = new uint8_t[WINDOW_WIDTH * WINDOW_HEIGHT * 4];
}

MapWindow::~MapWindow(){
	delete[] _pixels;
}

void MapWindow::open(int windowHeight, int windowWidth){
	SDLWindow::open(windowHeight, windowWidth);
  delete [] _pixels;
  _pixels = new uint8_t[windowWidth * windowHeight * 4];
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

void MapWindow::resizeWindow(int windowHeight, int windowWidth){
	SDLWindow::open(windowHeight, windowWidth);
  delete [] _pixels;
  _pixels = new uint8_t[windowWidth * windowHeight * 4];
  for(int i=0; i<windowWidth*windowHeight; i++){
    _pixels[i*4] = 0xFF;
    _pixels[i*4+1] = 0xFF;
    _pixels[i*4+2] = 0xFF;
    _pixels[i*4+3] = 0xFF;
  }
}

void MapWindow::renderPixels(){
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

void MapWindow::drawPixel(int x, int y, int r, int g, int b){
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

void MapWindow::drawMap(Map* m){
  m->mapDrawnBy = this;
  m->allowDrawMap = false;
  open();
  SDL_Event e;
  SDL_PollEvent(&e);
  cout << "Write a number: ";
  int a; cin >> a; cout << "you inputted " << a << endl;
  while(e.type != SDL_QUIT /*&& e.type != SDL_KEYDOWN*/ && requestClose != true){
    SDL_PollEvent(&e);
    //if(e.type == SDL_KEYDOWN)
      //cout << "Key " << e.key.keysym.sym << " map" << endl;
    if(e.type == SDL_WINDOWEVENT && e.window.event==SDL_WINDOWEVENT_SIZE_CHANGED)
      cout << "Window " << (int)e.window.windowID << " map" << endl;
    if((m->runningLogic && m->allowDrawMap) || !m->runningLogic){
      m->draw(this);
      m->allowDrawMap = false;
    }
  }
  close();
  m->mapDrawnBy = NULL;
}
