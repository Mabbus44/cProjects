#ifndef DAY11_H
#define DAY11_H
#include <iostream>
#include <vector>
#include "Common.h"
#include <list>

namespace Day11ns{
  using namespace std;

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

  enum Operation {ADD, SUBSTRACT, DIVIDE, MULTIPLY};
  class Monkey
  {
    public:
      Monkey(){}
      Monkey(vector<vector<string>> input){load(input);}
      virtual ~Monkey(){}
      void load(vector<vector<string>> input);
      void output();
      void inspect();
      void throwItems(list<Monkey*>& monkeys);
      int id;
      list<__int64> items;
      Operation operation;
      string operandA;
      string operandB;
      int test;
      int throwToIfTrue;
      int throwToIfFalse;
      int inspectedItems = 0;
  };
}
#endif // DAY11_H
