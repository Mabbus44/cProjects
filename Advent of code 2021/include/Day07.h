#ifndef DAY07_H
#define DAY07_H
#include <iostream>
#include <vector>
#include "Common.h"
#include <stdlib.h>


class Day07
{
  public:
    Day07();
    virtual ~Day07();
    void part1(string filename);
    void part2(string filename);
    int dist(vector<int>& crabs, int pos, bool exponential=false);
    int avg(vector<int>& crabs);
    int fuelConsumtion[2000];
  protected:

  private:
};

#endif // DAY07_H
