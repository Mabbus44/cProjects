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

double LNGreaterThan::compute(){
  if(_computeDone)
    return _computeResult;
  _computeDone = true;
  if(_parents.size() == 0)
    _computeResult = 0.0;
  if(_parents.size() == 1)
    _computeResult = _parents[0]->compute();
  if(_parents.size() > 1){
    if(_parents[0]->compute() > _parents[1]->compute())
      _computeResult = _parents[0]->compute();
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
