#include "Neurons/SNHerbivoreDist.h"
#include "Enteties/Entity.h"
#include "Map.h"
using namespace std;

SNHerbivoreDist::SNHerbivoreDist(Animal* parent, int type)
{
  _family = SENSOR_NEURON;
  _type = type;
  _parent = parent;
}

SNHerbivoreDist::~SNHerbivoreDist()
{
  //dtor
}

double SNHerbivoreDist::compute(){
  if(_computeDone)
    return _computeResult;
  _computeDone = true;
  int dir;
  switch(_type){
    case SN_HERBIVORE_DIST_N:
      dir = NORTH;
      break;
    case SN_HERBIVORE_DIST_S:
      dir = SOUTH;
      break;
    case SN_HERBIVORE_DIST_E:
      dir = EAST;
      break;
    case SN_HERBIVORE_DIST_W:
      dir = WEST;
      break;
  }
  distToResult(_parent->closestEntity(HERBIVORE, dir));
  return _postCompute();
}

Neuron* SNHerbivoreDist::deepCopy(Animal* parent){
  Neuron* ret = new SNHerbivoreDist(parent, _type);
  SensorNeuron::addToCopy(ret);
  return ret;
}
