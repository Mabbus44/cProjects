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

double LNAnd::compute(){
  if(_computeDone)
    return _computeResult;
  _computeDone = true;
  _computeResult = 1.0;
  for(Neuron* n : _parents)
    if(n->compute() < _computeResult)
      _computeResult = n->compute();
  return _postCompute();
}

Neuron* LNAnd::deepCopy(Animal* parent){
  Neuron* ret = new LNAnd(parent);
  LogicNeuron::addToCopy(ret);
  return ret;
}
