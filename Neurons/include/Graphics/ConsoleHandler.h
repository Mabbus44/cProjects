#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include <iostream>
#include <vector>
#include "Map.h"

using namespace std;

class Instruction{
  public:
    Instruction(){};
    Instruction(const Instruction& other){inst=other.inst; args=other.args;}
    Instruction(int inst, vector<int> args={}){this->inst=inst; this->args=args;}
    ~Instruction(){};
    int inst;
    vector<int> args;
};

class ConsoleHandler
{
  public:
    ConsoleHandler();
    virtual ~ConsoleHandler();
    void run();
    vector<Instruction> instructions;
    int mapId, animalType, animalId, neuronId;
  private:
    void outputMaps(vector<int> args);
    void outputAnimal(Map* m, string type, vector<int> args);
    void outputNeuron(Animal* a, vector<int> args);
    void outputMapsOneline();
    void runSimulation(Map* m, int steps);
    vector<int> argsToInt(string args);
    vector<string> argsTostr(string args);
};

#endif // CONSOLEHANDLER_H
