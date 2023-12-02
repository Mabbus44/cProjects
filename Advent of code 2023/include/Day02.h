#ifndef DAY02_H
#define DAY02_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

const string GREEN = "green";
const string RED = "red";
const string BLUE = "blue";

class Pick{
  public:
    Pick() {}
    Pick(string input) {load(input);}
    virtual ~Pick() {}
    void load(string input);
    void output();
    bool possiblePart1(vector<int> maxVals);
    vector<int> power() {return {_red, _green, _blue};}
  private:
    int _red=0;
    int _green=0;
    int _blue=0;
};

class Game{
  public:
    Game();
    Game(string input) {load(input);}
    virtual ~Game() {}
    void load(string input);
    void output();
    int possiblePart1(vector<int> maxVals);
    int power();
  private:
    vector<Pick> _picks;
    int _id = -1;
};

class Day02
{
  public:
    Day02();
    virtual ~Day02();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY02_H
