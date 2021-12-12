#ifndef DAY12_H
#define DAY12_H
#include <iostream>
#include <vector>
#include "Common.h"

enum types {START, END, SMALL, BIG};
class Cave{
  public:
  Cave(){};
  virtual ~Cave(){};
  void addConnection(Cave* newConnection);
  void output();
  int countPaths();
  int countPathsPart2(bool visitedTwice, string chain);
  string name;
  vector<Cave*> connections;
  bool visited;
  int type;
};

class Day12
{
  public:
    Day12();
    virtual ~Day12();
    void part1(string filename);
    void part2(string filename);
    Cave* addCave(string newName);
    void resetVisited();
    vector<Cave*> caves;
    Cave* startCave;
    Cave* endCave;
  protected:

  private:
};

#endif // DAY12_H
