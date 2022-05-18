#ifndef DAY19_H
#define DAY19_H
#include <iostream>
#include <vector>
#include "Common.h"
#include <map>

namespace Day19{
  class Rule{
    public:
      Rule(){};
      int load(vector<string> input);
      string followsRule(string message, bool& follows, map<int, Rule>& rules);
      vector<string> followsRule2(vector<string> message, map<int, Rule>& rules);
      void output();
      int index;
      vector<int> conditionA;
      vector<int> conditionB;
      char conditionC;
  };

  class Day19
  {
    public:
      Day19();
      virtual ~Day19();
      void part1(string filename);
      void part2(string filename);

    protected:

    private:
  };
}

#endif // DAY19_H
