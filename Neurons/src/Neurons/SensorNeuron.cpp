#include "Neurons/SensorNeuron.h"
#include <iostream>
using namespace std;
SensorNeuron::SensorNeuron()
{
  _family = SENSOR_NEURON;
  reRollProperties();
}

SensorNeuron::~SensorNeuron()
{
  //dtor
}

bool SensorNeuron::freeParentConnection(){
  return false;
}

Neuron* SensorNeuron::addToCopy(Neuron* n){
  Neuron::addToCopy(n);
  static_cast<SensorNeuron*>(n)->_bestDistance = _bestDistance;
  static_cast<SensorNeuron*>(n)->_maxDistance = _maxDistance;
  return n;
}

void SensorNeuron::reRollProperties(){
  Neuron::reRollProperties();
  _maxDistance = rand()%(SENSORS_MAX_DIST+1);
  _bestDistance = rand()%(_maxDistance+1);
}

void SensorNeuron::distToResult(int dist){
  if(dist > _maxDistance)
    dist = _maxDistance;
  if(dist > _bestDistance)
    _computeResult = 1.0 - (double)(dist-_bestDistance) / (double)(_maxDistance-_bestDistance);
  else{
    if(_bestDistance == 0)
      _computeResult = 1.0;
    else
      _computeResult = 1.0 - (double)(_bestDistance-dist) / (double)(_bestDistance);
  }
}
