#ifndef DAY18_H
#define DAY18_H
#include <iostream>
#include <vector>
#include "Common.h"

enum type{ADD, MUL};

class Expression{
  public:
    Expression(){};
    Expression(string input){load(input);};
    void load(string input);
    __int64 getVal();
    int type;
    __int64 val;
    vector<Expression> exps;

};

class Day18
{
  public:
    Day18();
    virtual ~Day18();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY18_H
