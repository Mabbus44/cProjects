#ifndef DAY09_H
#define DAY09_H
#include <iostream>
#include <vector>
#include "Common.h"

const int ROWS = 100;
const int COLS = 100;

class Day09
{
  public:
    Day09();
    virtual ~Day09();
    void part1(string filename);
    void part2(string filename);
    void calculateLowPoints();
    int calculateRiskLevel();
    int findBasin(int y, int x);
    vector<vector<int>> floorMap;
    vector<vector<bool>> inBasin;
    vector<int> lowPoints;

  protected:

  private:
};

#endif // DAY09_H
