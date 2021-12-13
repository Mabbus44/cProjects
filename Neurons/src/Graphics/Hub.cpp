#include "Graphics/Hub.h"

Hub::Hub()
{
  //ctor
}

Hub::~Hub()
{
  //dtor
}

void Hub::run(){
  async(&ConsoleHandler::run, &console);
  while(true){

  }
}

void Hub::parseConsoleInstruction(){
  switch(console.instructions[0].inst){
    case CREATE_MAP:
      createMap();
      break;
    case INIT_MAP:
      initMap();
      break;
    case DELETE_MAP:
      deleteMap();
      break;
    case VIEW_MAP:
      viewMap();
      break;
    case RUN_SIMULATION_STEPS:
      runSimulationSteps();
      break;
    case RUN_SIMULATION_GENERATIONS:
      runSimulationGenerations();
      break;
    case OUTPUT_MAPS:
      outputMaps();
      break;
    case OUTPUT_ANIMALS:
      outputAnimal();
      break;
    case OUTPUT_NEURONS:
      outputNeuron();
      break;
  }
}

void Hub::createMap(){
}

void Hub::initMap(){
}

void Hub::deleteMap(){
}

void Hub::viewMap(){
}

void Hub::runSimulationSteps(){
}

void Hub::runSimulationGenerations(){
}

void Hub::outputMaps(){
}

void Hub::outputAnimal(){
}

void Hub::outputNeuron(){
}
