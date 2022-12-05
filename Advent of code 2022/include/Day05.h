#ifndef DAY05_H
#define DAY05_H
#include <iostream>
#include <vector>
#include <list>
#include "Common.h"

using namespace std;

class Day05
{
  public:
    Day05();
    virtual ~Day05();
    void part1(string filename);
    void part2(string filename);
    void moveCrates(int count, int from, int to);
    void moveCrates2(int count, int from, int to);
    void clearStacks();
    list<char> string2list(string s);
    vector<list<char>> stacks;

  protected:

  private:
};

#endif // DAY05_H
