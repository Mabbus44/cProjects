#ifndef DAY11_H
#define DAY11_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Coord{
public:
  Coord(){}
  Coord(int x, int y) {_x = x; _y = y;}
  virtual ~Coord(){}
  int dist(Coord& other) {return abs(_x-other.x()) + abs(_y-other.y());}
  int x() {return _x;}
  int y() {return _y;}
private:
  int _x;
  int _y;
};

class Universe{
public:
  Universe(){}
  virtual ~Universe(){}
  void map(vector<vector<char>>& map) {_map = map;}
  void expandUniverse();
  void setGalaxies();
  void output();
  int galaxyDistances();
  void setEmptyLines();
  __int64 galaxyDistancesWithEmptyLines();
private:
  vector<vector<char>> _map;
  vector<Coord> _galaxies;
  vector<int> _emptyRows;
  vector<int> _emptyCols;
};

class Day11
{
  public:
    Day11();
    virtual ~Day11();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY11_H
