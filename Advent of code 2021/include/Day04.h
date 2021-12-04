#ifndef DAY04_H
#define DAY04_H
#include <iostream>
#include <vector>
#include "Common.h"

class BingoField{
public:
  BingoField(){};
  BingoField(const BingoField &f) {num = f.num; crossed = f.crossed; }
  ~BingoField(){};
  int num;
  bool crossed = false;
};

class BingoBoard{
public:
  BingoBoard(){};
  ~BingoBoard(){};
  bool loadBoard(vector<vector<int>>& input);
  void output();
  bool hasBingo();
  void drawNumber(vector<int>& drawnNumbers);
  int getScore();
  vector<vector<BingoField>> board;
  int lastNum;
  int drawnCount=0;
  int score=-1;
};

class Day04
{
  public:
    Day04();
    virtual ~Day04();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY04_H
