#include "Neurons/SNGrassDist.h"
#include "Enteties/Entity.h"
#include "Map.h"
using namespace std;

SNGrassDist::SNGrassDist(Animal* parent, int type)
{
  _family = SENSOR_NEURON;
  _type = type;
  _parent = parent;
}

SNGrassDist::~SNGrassDist()
{
  //dtor
}

double SNGrassDist::compute(int computeId){
  if(_computeId==computeId)
    return _computeResult;
  _computeId = computeId;
  int dir;
  switch(_type){
    case SN_GRASS_DIST_N:
      dir = NORTH;
      break;
    case SN_GRASS_DIST_S:
      dir = SOUTH;
      break;
    case SN_GRASS_DIST_E:
      dir = EAST;
      break;
    case SN_GRASS_DIST_W:
      dir = WEST;
      break;
  }
  distToResult(_parent->closestEntity(PLANT, dir));
  return _postCompute();
}

Neuron* SNGrassDist::deepCopy(Animal* parent){
  Neuron* ret = new SNGrassDist(parent, _type);
  SensorNeuron::addToCopy(ret);
  return ret;
}
