#ifndef DAY20_H
#define DAY20_H
#include <iostream>
#include <vector>
#include "Common.h"
#include <tuple>

enum SIDES{NO_SIDE, TOP, LEFT, RIGHT, BOTTOM};
enum REVS{NOT_REVERSED, REVERSED};

struct Coord{
  int y;
  int x;
};

class Tile{
public:
  Tile(){};
  Tile(int id, vector<string> input){load(id, input);};
  void load(int id, vector<string> input);
  void manipulate(int rot, int revX, int revY);
  tuple<int, int> matchSide(char side[10]);
  void output();
  string sides[4];
  string reversedSides[4];
  char pic[10][10];
  int id;
  int matchCount[4];
};

class Day20
{
  public:
    Day20();
    virtual ~Day20();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY20_H
