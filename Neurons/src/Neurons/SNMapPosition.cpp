#include "Neurons/SNMapPosition.h"
#include "Enteties/Entity.h"
#include "Map.h"

using namespace std;

SNMapPosition::SNMapPosition(Animal* parent, int type)
{
  _family = SENSOR_NEURON;
  _type = type;
  _parent = parent;
}

SNMapPosition::~SNMapPosition()
{
  //dtor
}

double SNMapPosition::compute(int computeId){
  if(_computeId==computeId)
    return _computeResult;
  _computeId = computeId;
  switch(_type){
    case SN_MAP_POSITION_XMIN:
      _computeResult = 1.0 - (double)(MAP_WIDTH-_parent->posX()) / (double)(MAP_WIDTH);
      break;
    case SN_MAP_POSITION_XMAX:
      _computeResult = (double)(MAP_WIDTH-_parent->posX()) / (double)(MAP_WIDTH);
      break;
    case SN_MAP_POSITION_YMIN:
      _computeResult = 1.0 - (double)(MAP_WIDTH-_parent->posY()) / (double)(MAP_HEIGHT);
      break;
    case SN_MAP_POSITION_YMAX:
      _computeResult = (double)(MAP_WIDTH-_parent->posY()) / (double)(MAP_HEIGHT);
      break;
  }
  return _postCompute();
}

Neuron* SNMapPosition::deepCopy(Animal* parent){
  Neuron* ret = new SNMapPosition(parent, _type);
  SensorNeuron::addToCopy(ret);
  return ret;
}
