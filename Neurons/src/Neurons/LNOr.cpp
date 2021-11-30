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

double LNOr::compute(){
  if(_computeDone)
    return _computeResult;
  _computeDone = true;
  _computeResult = 0.0;
  for(Neuron* n : _parents)
    if(n->compute() > _computeResult)
      _computeResult = n->compute();
  return _postCompute();
}

Neuron* LNOr::deepCopy(Animal* parent){
  Neuron* ret = new LNOr(parent);
  LogicNeuron::addToCopy(ret);
  return ret;
}
