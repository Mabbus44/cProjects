#ifndef DAY14_H
#define DAY14_H
#include <iostream>
#include <vector>
#include "Common.h"


class Day14
{
  public:
    Day14();
    virtual ~Day14();
    void part1(string filename);
    void part2(string filename);
    void loadInput(string filename);
    bool insertAtPosition(int p);
    void saveOldState();
    void insertPart2();
    int countChar(char c);
    vector<vector<string>> rules;
    vector<vector<int>> rulesPart2;
    string state;
    string startState;
    int64_t pairs[26*26];
    int64_t letters[26];
    int64_t oldPairs[26*26];
    int64_t oldLetters[26];
  protected:

  private:
};

#endif // DAY14_H
