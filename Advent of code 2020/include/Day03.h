#ifndef DAY03_H
#define DAY03_H
#include <iostream>
#include <vector>
#include "Common.h"


class Day03
{
  public:
    Day03();
    virtual ~Day03();
    void part1(string filename);
    void part2(string filename);
    void move(int x, int y);
    vector<vector<char>> treeMap;
    int posX=0, posY=0;

  protected:

  private:
};

#endif // DAY03_H
