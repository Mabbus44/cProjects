#ifndef DAY09_H
#define DAY09_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

enum Dir {RIGHT, LEFT, UPP, DOWN};
class Command;

class Day09
{
  public:
    Day09();
    virtual ~Day09();
    void part1(string filename);
    void part2(string filename);
    void executeCommand(Command c);
    void moveTail();
    void executeCommand2(Command c);
    void moveTail2(int tailId, int followX, int followY);
    int x;
    int y;
    int tailX;
    int tailY;
    int tail2X[9];
    int tail2Y[9];
    BtNode<string> tailHistory;
  protected:

  private:
};

class Command
{
  public:
    Command(){}
    Command(string dir, int steps){load(dir, steps);}
    virtual ~Command(){}
    void load(string dir, int steps);
    Dir dir;
    int steps;
};

#endif // DAY09_H

