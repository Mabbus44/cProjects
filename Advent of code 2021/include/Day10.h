#ifndef DAY10_H
#define DAY10_H
#include <iostream>
#include <vector>
#include "Common.h"


class Day10
{
  public:
    Day10();
    virtual ~Day10();
    void part1(string filename);
    void part2(string filename);
    int evaluateLine(vector<char>& line);
    int64_t autoComplete(vector<char>& line);

  protected:

  private:
};

#endif // DAY10_H
