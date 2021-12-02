#ifndef DAY02_H
#define DAY02_H
#include <iostream>
#include <vector>
#include "Common.h"

enum dir{FORWARD, UP, DOWN};

using namespace std;

class Day02
{
  public:
    Day02();
    virtual ~Day02();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY02_H
