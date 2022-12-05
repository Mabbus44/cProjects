#ifndef DAY03_H
#define DAY03_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Day03
{
  public:
    Day03();
    virtual ~Day03();
    char findDouplicate(string backpack);
    char findCommon(vector<string> group);
    int priority(char c);
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY03_H
