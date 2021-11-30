#include "Neurons/SNCarnivoreDist.h"
#include <iostream>
#include "Enteties/Entity.h"
#include "Map.h"
using namespace std;

SNCarnivoreDist::SNCarnivoreDist(Animal* parent, int type)
{
  _family = SENSOR_NEURON;
  _type = type;
  _parent = parent;
}

SNCarnivoreDist::~SNCarnivoreDist()
{
  //dtor
}

double SNCarnivoreDist::compute(){
  if(_computeDone)
    return _computeResult;
  _computeDone = true;
  int dir;
  switch(_type){
    case SN_CARNIVORE_DIST_N:
      dir = NORTH;
      break;
    case SN_CARNIVORE_DIST_S:
      dir = SOUTH;
      break;
    case SN_CARNIVORE_DIST_E:
      dir = EAST;
      break;
    case SN_CARNIVORE_DIST_W:
      dir = WEST;
      break;
  }
  distToResult(_parent->closestEntity(CARNIVORE, dir));
  return _postCompute();
}

Neuron* SNCarnivoreDist::deepCopy(Animal* parent){
  Neuron* ret = new SNCarnivoreDist(parent, _type);
  SensorNeuron::addToCopy(ret);
  return ret;
}
