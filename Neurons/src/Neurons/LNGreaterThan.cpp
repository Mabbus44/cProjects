#include "Neurons/LNGreaterThan.h"
#include <iostream>
using namespace std;

LNGreaterThan::LNGreaterThan(Animal* parent)
{
  _family = LOGIC_NEURON;
  _type = LN_GREATER_THAN;
  _parent = parent;
}

LNGreaterThan::~LNGreaterThan()
{
  //dtor
}

double LNGreaterThan::compute(int computeId){
  if(_computeId==computeId)
    return _computeResult;
  _computeId = computeId;
  if(_parents.size() == 0)
    _computeResult = 0.0;
  if(_parents.size() == 1)
    _computeResult = _parents[0]->compute(computeId);
  if(_parents.size() > 1){
    if(_parents[0]->compute(computeId) > _parents[1]->compute(computeId))
      _computeResult = _parents[0]->compute(computeId);
    else
      _computeResult = 0.0;
  }
  return _postCompute();
}

Neuron* LNGreaterThan::deepCopy(Animal* parent){
  Neuron* ret = new LNGreaterThan((parent));
  LogicNeuron::addToCopy(ret);
  return ret;
}
