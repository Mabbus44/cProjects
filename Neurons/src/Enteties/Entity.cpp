#include "Enteties/Entity.h"
#include <math.h>

using namespace std;

Entity::Entity()
{
}

Entity::~Entity()
{
  //dtor
}

bool Entity::isInDirection(int x, int y, int direction)//Returns true if (this) is in (direction) of (x, y)
{
  int diffX = _posX-x;
  int diffY = _posY-y;
  switch(direction){
    case NORTH:
      if(diffY<0 && abs(diffY)>=abs(diffX))
        return true;
      break;
    case SOUTH:
      if(diffY>0 && abs(diffY)>=abs(diffX))
        return true;
      break;
    case EAST:
      if(diffX>0 && abs(diffX)>=abs(diffY))
        return true;
      break;
    case WEST:
      if(diffX<0 && abs(diffX)>=abs(diffY))
        return true;
      break;
  }
  return false;
}

int Entity::distance(int x, int y)
{
  return sqrt((x-_posX)*(x-_posX)+(y-_posY)*(y-_posY));
}

void Entity::output(string tab, int level){
  switch(level){
    case OUTPUT_ONELINE:
      cout << tab << "Address: " << this << " Pos: (" << _posX << ", " << _posY << ")" << " Type: " << _type << " Parent: " << _parent;
      break;
    case OUTPUT_OVERVIEW:
    case OUTPUT_DEEP:
    case OUTPUT_ALL:
      cout << tab << "Address: " << this << endl;
      cout << tab << "Pos: (" << _posX << ", " << _posY << ")" << endl;
      cout << tab << "Type: " << _type << endl;
      cout << tab << "Parent: " << _parent << endl;
      break;
  }
}

void Entity::draw(MapWindow* window){
  switch(_type){
    case CARNIVORE:
      window->drawPixel(_posX, _posY, 0xFF, 0, 0);
      break;
    case HERBIVORE:
      window->drawPixel(_posX, _posY, 0, 0, 0xFF);
      break;
    case PLANT:
      window->drawPixel(_posX, _posY, 0, 0xFF, 0);
      break;
  }
}
