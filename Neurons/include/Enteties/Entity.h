#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Constants.h"
#include "Graphics/SDLWindow.h"
using namespace std;
class Map;

class Entity
{
  public:
    Entity();
    virtual ~Entity();
    bool isInDirection(int x, int y, int direction);
    int distance(int x, int y);
    void draw(MapWindow* window, bool selected=false);
    void output(string tab, int level);
    int index(){return _index;}
    int posX(){return _posX;}
    int posY(){return _posY;}

  protected:
    int _posX, _posY;
    int _type;
    Map* _parent=NULL;
    int _index;
};

#endif // ENTITY_H
