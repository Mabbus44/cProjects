#include "Neurons/OutputNeuron.h"
#include <iostream>
using namespace std;

OutputNeuron::OutputNeuron()
{
  _family = OUTPUT_NEURON;
}

OutputNeuron::~OutputNeuron()
{
  //dtor
}

bool OutputNeuron::freeChildConnection(){
  return false;;
}

double OutputNeuron::compute(){
  if(_computeDone)
    return _computeResult;
  _computeDone = true;
  _computeResult = -1.0;
  for(Neuron* n : _parents)
    if(n->compute() > _computeResult)
      _computeResult = n->compute();
  return _postCompute();
}

Neuron* OutputNeuron::addToCopy(Neuron* n){
  Neuron::addToCopy(n);
  return n;
}
