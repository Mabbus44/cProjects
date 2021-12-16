#ifndef HUB_H
#define HUB_H

#include "Graphics/ConsoleHandler.h"
#include <thread>
#include <future>

class SimulationJob{
  public:
    SimulationJob(){};
    SimulationJob(const SimulationJob& other){simulationType=other.simulationType; stepsLeft=other.stepsLeft, m=other.m;}
    SimulationJob(int simulationType, int stepsLeft, Map* m){this->simulationType=simulationType; this->stepsLeft=stepsLeft; this->m=m;}
    ~SimulationJob(){};
    int simulationType;
    int stepsLeft;
    Map* m;
};

class Hub
{
  public:
    Hub();
    virtual ~Hub();
    void run();

  protected:

  private:
    void createMap(vector<int> args);
    void initMap(vector<int> args);
    void deleteMap(vector<int> args);
    void viewMap(vector<int> args);
    void runSimulationSteps(vector<int> args);
    void runSimulationGenerations(vector<int> args);
    void copyMap(vector<int> args);
    void outputSimulationStatus(vector<int> args);
    void outputMaps(vector<int> args);
    void outputMapsOneline(vector<int> args);
    void outputAnimal(vector<int> args);
    void outputNeuron(vector<int> args);
    void mutateNeurons(vector<int> args);
    void parseConsoleInstructions();
    void handleSdlEvents();
    void handleWindowEvents(SDL_Event& e);
    void handleKeyEvents(SDL_Event& e);
    void runSimulations();
    Map* getMap(int& i);
    MapWindow mapWindow;
    NeuronsWindow neuronWindow;
    ConsoleHandler console;
    vector<Map*> _maps;
    vector<SimulationJob> _jobs;
};

#endif // HUB_H
