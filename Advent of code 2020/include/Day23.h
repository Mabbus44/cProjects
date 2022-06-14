#ifndef DAY23_H
#define DAY23_H
#include <iostream>
#include <vector>
#include "Common.h"

class Cup{
public:
  Cup(){};
  Cup(int num){number=num;}
  int number;
  Cup* numberBefore;
  Cup* cupAfter;
};

class Day23
{
  public:
    Day23();
    virtual ~Day23();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY23_H
