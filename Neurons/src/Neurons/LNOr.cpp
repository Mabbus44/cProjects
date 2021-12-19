#include "Neurons/LNOr.h"
#include <iostream>
using namespace std;

LNOr::LNOr(Animal* parent)
{
  _family = LOGIC_NEURON;
  _type = LN_OR;
  _parent = parent;
}

LNOr::~LNOr()
{
  //dtor
}

double LNOr::compute(int computeId){
  if(_computeId==computeId)
    return _computeResult;
  _computeId = computeId;
  _computeResult = 0.0;
  for(Neuron* n : _parents)
    if(n->compute(computeId) > _computeResult)
      _computeResult = n->compute(computeId);
  return _postCompute();
}

Neuron* LNOr::deepCopy(Animal* parent){
  Neuron* ret = new LNOr(parent);
  LogicNeuron::addToCopy(ret);
  return ret;
}
