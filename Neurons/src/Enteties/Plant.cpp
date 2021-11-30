#include "Enteties/Plant.h"

Plant::Plant(Map* parent, int posX, int posY, int index){
  _parent = parent;
  _posX = posX;
  _posY = posY;
  _index = index;
  _type = PLANT;
}

Plant::~Plant()
{
  //dtor
}

Plant* Plant::deepCopy(Map* parent){
  Plant* newPlant = new Plant(parent, _posX, _posY, _index);
  return newPlant;
}
