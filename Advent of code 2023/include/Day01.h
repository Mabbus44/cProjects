#ifndef DAY01_H
#define DAY01_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Day01
{
  public:
    Day01();
    virtual ~Day01();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
    size_t findLast(string subStr, string str);
};

#endif // DAY01_H
