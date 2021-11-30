#ifndef PLANT_H
#define PLANT_H

#include "Enteties/Entity.h"

class Plant: public Entity
{
  public:
    Plant();
    Plant(Map* parent, int posX, int posY, int index);
    virtual ~Plant();
    Plant* deepCopy(Map* parent);

  protected:

  private:
};

#endif // PLANT_H
