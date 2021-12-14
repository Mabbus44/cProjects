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
    void copyMap();
    void outputMaps();
    void outputAnimal();
    void outputNeuron();
    void parseConsoleInstruction();
    Map* getMap(int& i);
    MapWindow mapWindow;
    NeuronsWindow neuronWindow;
    ConsoleHandler console;
    vector<Map*> _maps;
};

#endif // HUB_H
