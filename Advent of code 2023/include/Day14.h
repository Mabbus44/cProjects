#ifndef DAY14_H
#define DAY14_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Dish{
public:
  Dish(){}
  Dish(vector<vector<char>> input) {load(input);}
  virtual ~Dish(){}
  bool operator==(Dish& other);
  void load(vector<vector<char>> input);
  void moveNorth();
  void moveWest();
  void moveSouth();
  void moveEast();
  void cycle();
  void output();
  int calcLoad();
private:
  vector<vector<char>> _dish;
};

class Day14
{
  public:
    Day14();
    virtual ~Day14();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY14_H
