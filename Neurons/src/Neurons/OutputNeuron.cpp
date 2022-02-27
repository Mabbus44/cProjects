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

double OutputNeuron::compute(int computeId){
  if(_computeId==computeId)
    return _computeResult;
  _computeId = computeId;
  if(_factor>0){
    _computeResult = -1.0;
    for(Neuron* n : _parents)
      if(n->compute(computeId) > _computeResult)
        _computeResult = n->compute(computeId);
  }else{
    _computeResult = 1.0;
    for(Neuron* n : _parents)
      if(n->compute(computeId) < _computeResult)
        _computeResult = n->compute(computeId);
  }
  return _postCompute();
}

Neuron* OutputNeuron::addToCopy(Neuron* n){
  Neuron::addToCopy(n);
  return n;
}
