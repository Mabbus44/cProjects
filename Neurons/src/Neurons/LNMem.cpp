#include "Neurons/LNMem.h"
#include <iostream>
using namespace std;

LNMem::LNMem(Animal* parent)
{
  _family = LOGIC_NEURON;
  _type = LN_MEM;
  _parent = parent;
}

LNMem::~LNMem()
{
  //dtor
}

bool LNMem::freeParentConnection(){
  return _parents.size() == 0;
}

bool LNMem::freeChildConnection(){
  return _children.size() == 0;
}

double LNMem::compute(int computeId){
  _computeId = computeId;
  return _computeResult;
}

void LNMem::computeMem(int computeId){
  _computeId = computeId;
  for(Neuron* n : _parents)
    _computeResult = n->compute(computeId);
}

Neuron* LNMem::deepCopy(Animal* parent){
  Neuron* ret = new LNMem(parent);
  LogicNeuron::addToCopy(ret);
  return ret;
}
