#ifndef DAY13_H
#define DAY13_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Field{
public:
  Field(){}
  Field(vector<vector<char>>& input) {load(input);}
  virtual ~Field(){}
  void load(vector<vector<char>>& input);
  void findMirror();
  void findMirror2();
  int score();
  int score2();
  bool identicalRows(int rowA, int rowB);
  bool identicalCols(int colA, int colB);
  int diffCountRows(int rowA, int rowB);
  int diffCountCols(int colA, int colB);
  void output();
private:
  vector<vector<char>> _field;
  int _score = -1;
  int _score2 = -1;
};

class Day13
{
  public:
    Day13();
    virtual ~Day13();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY13_H
