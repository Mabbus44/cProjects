#ifndef DAY21_H
#define DAY21_H
#include <iostream>
#include <vector>
#include "Common.h"

class GameState{
public:
  GameState(){}
  GameState(int p1, int p2, int s1, int s2, int64_t c){pos[0] = p1; pos[1] = p2; score[0] = s1; score[1]=s2; count=c;}
  GameState(const GameState& g){pos[0] = g.pos[0]; pos[1] = g.pos[1]; score[0] = g.score[0]; score[1]=g.score[1]; count=g.count;}
  virtual ~GameState(){}
  int pos[2];
  int score[2];
  int64_t count=0;
};

class Day21
{
  public:
    Day21();
    virtual ~Day21();
    void part1(string filename);
    void part2(string filename);
    int64_t rollDie(int times);
    int64_t die;
    int64_t pos[2];
    int64_t score[2];

  protected:

  private:
};

#endif // DAY21_H
