#include "Neurons/LNAdd.h"
#include <iostream>
using namespace std;

LNAdd::LNAdd(Animal* parent)
{
  _family = LOGIC_NEURON;
  _type = LN_ADD;
  _parent = parent;
}

LNAdd::~LNAdd()
{
  //dtor
}

double LNAdd::compute(int computeId){
  if(_computeId==computeId)
    return _computeResult;
  _computeId = computeId;
  _computeResult = 0.0;
  for(Neuron* n : _parents)
    _computeResult = _computeResult + n->compute(computeId);
  return _postCompute();
}

Neuron* LNAdd::deepCopy(Animal* parent){
  Neuron* ret = new LNAdd(parent);
  LogicNeuron::addToCopy(ret);
  return ret;
}
