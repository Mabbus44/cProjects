#ifndef DAY06_H
#define DAY06_H
#include <iostream>
#include <vector>
#include "Common.h"

class Day06
{
  public:
    Day06();
    virtual ~Day06();
    void part1(string filename);
    void part2(string filename);
    int64_t countOffspring(int days, int ageLeft);

  protected:

  private:
};

#endif // DAY06_H
