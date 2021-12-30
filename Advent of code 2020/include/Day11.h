#ifndef DAY11_H
#define DAY11_H
#include <iostream>
#include <vector>
#include "Common.h"


class Day11
{
  public:
    Day11();
    virtual ~Day11();
    int occupiedNeighbours(int x, int y);
    int occupiedNeighboursPart2(int x, int y);
    void part1(string filename);
    void part2(string filename);
    void output();
    vector<vector<char>> seats;
    vector<vector<char>> newSeats;

  protected:

  private:
};

#endif // DAY11_H
