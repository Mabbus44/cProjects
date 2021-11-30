#include "Neurons/LogicNeuron.h"

LogicNeuron::LogicNeuron()
{
  _family = LOGIC_NEURON;
}

LogicNeuron::~LogicNeuron()
{
  //dtor
}

Neuron* LogicNeuron::addToCopy(Neuron* n){
  Neuron::addToCopy(n);
  return n;
}
