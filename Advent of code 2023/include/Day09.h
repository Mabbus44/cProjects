#ifndef DAY09_H
#define DAY09_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class ValHistory{
public:
  ValHistory(){}
  ValHistory(string input){load(input);}
  ValHistory(vector<__int64> input);
  virtual ~ValHistory(){}
  void load(string input);
  void clear();
  __int64 getNext();
  __int64 getPrev();
  void setInc();

private:
  vector<__int64> _history;
  ValHistory* _inc = nullptr;
  __int64 _constInc;
};

class Day09
{
  public:
    Day09();
    virtual ~Day09();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY09_H
