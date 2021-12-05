#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include <iostream>
#include <vector>
#include "Map.h"
#include <thread>
#include <future>

using namespace std;

class ConsoleHandler
{
  public:
    ConsoleHandler();
    virtual ~ConsoleHandler();
    void run();
  private:
    void createMap(vector<int> args);
    void initMap(vector<int> args);
    void deleteMap(vector<int> args);
    void viewMap(vector<int> args);
    void runSimulationSteps(vector<int> args);
    void runSimulationGenerations(vector<int> args, bool copyMap=false);
    void outputMaps(vector<int> args);
    void outputAnimal(Map* m, string type, vector<int> args);
    void outputNeuron(Animal* a, vector<int> args);
    void outputMapsOneline();
    void runSimulation(Map* m, int steps);
    Map* getMap(int& i);
    SDLWindow mapWindow;
    SDLWindow neuronWindow;
    future<void> mapWindowRet;
    future<void> neuronWindowRet;
    vector<int> argsToInt(string args);
    vector<string> argsTostr(string args);
    vector<Map*> _maps;
};

#endif // CONSOLEHANDLER_H
