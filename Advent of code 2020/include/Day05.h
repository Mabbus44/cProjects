#ifndef DAY05_H
#define DAY05_H
#include <iostream>
#include <vector>
#include "Common.h"


class Day05
{
  public:
    Day05();
    virtual ~Day05();
    void part1(string filename);
    void part2(string filename);
    int getRow(string line);
    int getSeat(string line);

  protected:

  private:
};

#endif // DAY05_H
