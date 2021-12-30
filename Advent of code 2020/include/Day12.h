#ifndef DAY12_H
#define DAY12_H
#include <iostream>
#include <vector>
#include "Common.h"

enum dir {N, E, S, W};

class Nav{
public:
  Nav(){};
  virtual ~Nav(){};
  void load(string line);
  char inst;
  int val;
};

class Day12
{
  public:
    Day12();
    virtual ~Day12();
    void part1(string filename);
    void part2(string filename);
    int charDirToInt(char dir);
    void moveDir(int dir, int dist);
    void moveWPDir(int dir, int dist);
    void rotWP(int dist);
    void moveToWP(int dist);
    vector<Nav> instructions;
    int x, y;
    int wpx, wpy;
    int facingDirection;

  protected:

  private:
};

#endif // DAY12_H
