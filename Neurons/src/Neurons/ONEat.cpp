#include "Neurons/ONEat.h"

ONEat::ONEat(Animal* parent)
{
  _family = OUTPUT_NEURON;
  _type = ON_EAT;
  _parent = parent;
}

ONEat::~ONEat()
{
  //dtor
}

Neuron* ONEat::deepCopy(Animal* parent){
  Neuron* ret = new ONEat(parent);
  OutputNeuron::addToCopy(ret);
  return ret;
}
