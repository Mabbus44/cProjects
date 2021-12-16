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
    int mapId, animalId, neuronId;
    string animalType;
  private:
    void outputMaps(vector<int> args);
    void outputAnimal(string type, vector<int> args);
    void outputNeuron(vector<int> args);
    void outputMapsOneline();
    vector<int> argsToInt(string args);
    vector<string> argsTostr(string args);
};

#endif // CONSOLEHANDLER_H
