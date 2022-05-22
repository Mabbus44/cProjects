#ifndef DAY21_H
#define DAY21_H
#include <iostream>
#include <vector>
#include "Common.h"

class Recepie{
  public:
    Recepie(){};
    Recepie(vector<string> input){load(input);};
    void load(vector<string> input);
    void output();
    vector<string> ingredients;
    vector<string> allergens;
};

class Day21
{
  public:
    Day21();
    virtual ~Day21();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY21_H
