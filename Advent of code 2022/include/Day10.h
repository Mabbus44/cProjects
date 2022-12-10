#ifndef DAY10_H
#define DAY10_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Day10
{
  public:
    Day10();
    virtual ~Day10();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

enum Instruction {ADDX, NOOP};

class Command
{
  public:
    Command(){}
    Command(vector<string> cmdParts){load(cmdParts);}
    virtual ~Command(){}
    void load(vector<string> cmdParts);
    Instruction instruction;
    int intArg0;
};

class CPU
{
  public:
    CPU(){}
    virtual ~CPU(){}
    void load(string fileName);
    void start(){currentCommand = commands.begin(); cpuCycle = 0; cpuCycleOnCurrentCommand = 0; registerX = 1;}
    bool runCpuCycle();
    vector<Command> commands;
    vector<Command>::iterator currentCommand;
    int cpuCycle;
    int cpuCycleOnCurrentCommand;
    int registerX;
};
#endif // DAY10_H
