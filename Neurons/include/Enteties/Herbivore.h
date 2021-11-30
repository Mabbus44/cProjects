#ifndef Herbivore_H
#define Herbivore_H

#include "Enteties/Animal.h"

class Herbivore: public Animal
{
  public:
    Herbivore();
    Herbivore(Map* parent, int posX, int posY, int index, int bellyFood=HERBIVORE_START_FOOD, bool initNeurons = true);
    virtual ~Herbivore();
    virtual void eat(){_bellyFood+=HERBIVORE_EAT_FOOD;}

  protected:

  private:
};

#endif // Herbivore_H
