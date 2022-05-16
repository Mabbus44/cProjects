#ifndef DAY16_H
#define DAY16_H
#include <iostream>
#include <vector>
#include "Common.h"

class Range{
  public:
    Range(){};
    Range(int mi, int ma){rangeMin = mi; rangeMax = ma;};
    int rangeMin;
    int rangeMax;
};

class Rule{
  public:
    Rule(){for(int i=0; i<20; i++) index.push_back(i);};
    Rule(vector<string> input){load(input);};
    void load(vector<string> input);
    bool inRange(int val);
    void output();
    string name;
    vector<Range> ranges;
    vector<int> index;
};

class Day16
{
  public:
    Day16();
    virtual ~Day16();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY16_H
