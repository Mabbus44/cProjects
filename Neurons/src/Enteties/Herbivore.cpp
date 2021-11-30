#include "Enteties/Herbivore.h"

Herbivore::Herbivore(Map* parent, int posX, int posY, int index, int bellyFood, bool initNeurons){
  _parent=parent;
  _posX=posX;
  _posY=posY;
  _index=index;
  _bellyFood=bellyFood;
  _type = HERBIVORE;
  if(initNeurons){
    generateNeurons();
    for(Neuron* n:_neurons){
      connectNeuronToChildren(n);
      connectNeuronToParents(n);
    }
  }
}

Herbivore::~Herbivore()
{
  //dtor
}
