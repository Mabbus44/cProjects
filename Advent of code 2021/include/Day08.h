#ifndef DAY08_H
#define DAY08_H
#include <iostream>
#include <vector>
#include "Common.h"


class Digit{
  public:
    Digit(){};
    Digit(const Digit& d);
    virtual ~Digit(){};
    void setDigit(string input);
    void output();
    int segmentCount();
    bool sharesSegment(Digit d);
    Digit inverse();
    bool segment[7];
    int numVal=-1;
};

class Day08
{
  public:
    Day08();
    virtual ~Day08();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY08_H
