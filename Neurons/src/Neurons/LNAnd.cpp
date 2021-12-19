#include "Neurons/LNAnd.h"
#include <iostream>
using namespace std;

LNAnd::LNAnd(Animal* parent)
{
  _family = LOGIC_NEURON;
  _type = LN_AND;
  _parent = parent;
}

LNAnd::~LNAnd()
{
  //dtor
}

double LNAnd::compute(int computeId){
  if(_computeId==computeId)
    return _computeResult;
  _computeId = computeId;
  _computeResult = 1.0;
  for(Neuron* n : _parents)
    if(n->compute(computeId) < _computeResult)
      _computeResult = n->compute(computeId);
  return _postCompute();
}

Neuron* LNAnd::deepCopy(Animal* parent){
  Neuron* ret = new LNAnd(parent);
  LogicNeuron::addToCopy(ret);
  return ret;
}
