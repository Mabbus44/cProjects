#ifndef HUB_H
#define HUB_H

#include "Graphics/ConsoleHandler.h"
#include <thread>
#include <future>


class Hub
{
  public:
    Hub();
    virtual ~Hub();
    void run();

  protected:

  private:
    void createMap();
    void initMap();
    void deleteMap();
    void viewMap();
    void runSimulationSteps();
    void runSimulationGenerations();
    void outputMaps();
    void outputAnimal();
    void outputNeuron();
    void parseConsoleInstruction();
    MapWindow mapWindow;
    NeuronsWindow neuronWindow;
    ConsoleHandler console;
};

#endif // HUB_H
