#ifndef DAY12_H
#define DAY12_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class CountPerBunch{
// Count combination for one count of covered ### bunch
public:
  CountPerBunch(){}
  CountPerBunch(int b, __int64 c){bunchCount = b; count = c;}
  virtual ~CountPerBunch(){}
  void output() {cout << "(" << bunchCount << "," << count << ")";}
  int bunchCount;
  __int64 count;
};

class Combination{
// Count of combinations for one position
public:
  Combination(){}
  Combination(int p, vector<CountPerBunch> c){pos = p; count = c;}
  virtual ~Combination(){}
  void output();
  int pos;
  vector<CountPerBunch> count;
};

class Group{
public:
  Group(){}
  Group(Group* b, int l) {_biggerSibling = b; _groupLen = l;}
  virtual ~Group(){}
  void biggerSibling(Group* c){_biggerSibling = c;}
  int groupLen(){return _groupLen;}
  void addCombination(int pos, int bunchCount);
  vector<CountPerBunch> combinationsBefore(int pos);
  void output();
private:
  Group* _biggerSibling = nullptr;
  vector<Combination> _combinations;
  int _groupLen;
};

class SpringGroup{
public:
  SpringGroup(){}
  SpringGroup(string input){load(input);}
  virtual ~SpringGroup(){}
  void load(string input);
  bool fits(int pos, int groupLen);
  bool restOk(int pos);
  int variations(int id, int pos, vector<int> history);
  int allVariations();
  __int64 allVariations2();
  int CoveredBunchCount(int pos, int groupLen);
  void output();
  void unfold();
private:
  vector<int> _groups;
  vector<Group*> _groupObjects;
  vector<char> _springs;
  int _bunchCount;
};

class Day12
{
  public:
    Day12();
    virtual ~Day12();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY12_H
