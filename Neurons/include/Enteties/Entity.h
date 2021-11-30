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
    void draw(SDLWindow* window);
    void output(string tab, int level);

  protected:
    int _posX, _posY;
    int _type;
    Map* _parent=NULL;
    int _index;
};

#endif // ENTITY_H
