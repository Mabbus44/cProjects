#ifndef DAY11_H
#define DAY11_H
#include <iostream>
#include <vector>
#include "Common.h"

class Dumbo{
  public:
    Dumbo(){};
    Dumbo (Dumbo& other) {energy=other.energy; flashed=other.flashed; spreadEnergy=other.spreadEnergy;}
    virtual ~Dumbo(){};
    int energy = 0;
    bool flashed = false;
    bool spreadEnergy = false;
};

class Day11
{
  public:
    Day11();
    virtual ~Day11();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY11_H
