#ifndef DAY25_H
#define DAY25_H
#include <iostream>
#include <vector>
#include "Common.h"

class Day25
{
  public:
    Day25();
    virtual ~Day25();
    void part1(string filename);
    void part2(string filename);
    bool eastFree(int x, int y);
    bool southFree(int x, int y);
    void checkAllEast();
    void checkAllSouth();
    bool moveAllEast();
    bool moveAllSouth();
    void output();
    char cMap[137][139];
    bool canMove[137][139];
    int sizeX = 139;
    int sizeY = 137;
  protected:

  private:
};

#endif // DAY25_H
