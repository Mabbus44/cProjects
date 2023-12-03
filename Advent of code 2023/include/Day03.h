#ifndef DAY03_H
#define DAY03_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

enum GridType {outOfBounds, none, number, symbol};
class Day03
{
  public:
    Day03();
    virtual ~Day03();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
    GridType getGridType(int x, int y);
    int getDigitCount(int x, int y);
    int getNumber(int x, int y, int digitCount);
    bool hasSymbolAboveOrBelow(int x, int y);
    vector<vector<char>> _grid;
    int gearRatio(int x, int y);
    int getNumberStartX(int x, int y);
    int getNumber(int x, int y);
};

#endif // DAY03_H
