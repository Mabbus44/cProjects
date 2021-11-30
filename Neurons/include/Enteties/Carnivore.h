#ifndef Carnivore_H
#define Carnivore_H

#include "Enteties/Animal.h"

class Carnivore: public Animal
{
  public:
    Carnivore();
    Carnivore(Map* parent, int posX, int posY, int index, int bellyFood=CARNIVORE_START_FOOD, bool initNeurons = true);
    virtual ~Carnivore();
    virtual void eat(){_bellyFood+=CARNIVORE_EAT_FOOD;}

  protected:

  private:
};

#endif // Carnivore_H
