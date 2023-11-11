#include "Entities.h"

Entity::Entity()
{
  //ctor
}

Entity::~Entity()
{
  //dtor
}

void Animal::decideAction(uint8_t* input){
  // As long as inputSize < 2^16 (65536) we wont get overflow if input and factor are 8 bit, and result 32 bit.
  int inputSize = INPUTS_PER_SQUARE * (SENSOR_RADIUS_SQUARES * 2 + 1) * (SENSOR_RADIUS_SQUARES * 2 + 1);
  int factorId = 0;
  int highestActionId = 0;
  uint32_t highestActionWeight = 0;
  uint32_t* actionWeight = new uint32_t[AnimalAction::COUNT];
  for(int actionId = 0; actionId < AnimalAction::COUNT; actionId++){
    actionWeight[actionId] = 0;
    for(int inputId=0; inputId<inputSize; inputId++)
      actionWeight[actionId] += (uint32_t)(_factors[factorId++]) * (uint32_t)(input[inputId]);
    if(actionWeight[actionId] > highestActionWeight){
      highestActionWeight = actionWeight[actionId];
      highestActionId = actionId;
    }
  }
  delete [] actionWeight;
  _action = (AnimalAction)highestActionId;
}

void Animal::addEnergy(int newEnergy){
  _energy += newEnergy;
  if(_energy > MAX_ENERGY)
    _energy = MAX_ENERGY;
}

bool Animal::removeEnergy(int lostEnergy){
  _energy -= lostEnergy;
  if(_energy <= 0){
    _energy = 0;
    return false;
  }
  return true;
}
