#include "Neurons/ONMove.h"

ONMove::ONMove(Animal* parent, int type)
{
  _family = OUTPUT_NEURON;
  _type = type;
  _parent = parent;
}

ONMove::~ONMove()
{
  //dtor
}

Neuron* ONMove::deepCopy(Animal* parent){
  Neuron* ret = new ONMove(parent, _type);
  OutputNeuron::addToCopy(ret);
  return ret;
}
