#ifndef DAY22_H
#define DAY22_H
#include <iostream>
#include <vector>
#include "Common.h"


class Day22
{
  public:
    Day22();
    virtual ~Day22();
    void part1(string filename);
    void part2(string filename);
    int runGame(vector<int> deck1, vector<int> deck2, vector<int> rounds);
    __int64 winnerScore;
  protected:

  private:
};

#endif // DAY22_H
