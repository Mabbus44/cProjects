#ifndef DAY23_H
#define DAY23_H
#include <iostream>
#include <vector>
#include "Common.h"

enum letters {A,B,C,D};
enum moveTypes {HOME_HOME, HOME_LEFTSAFE, HOME_RIGHTSAFE, HOME_MIDDLESAFE,
                LEFTSAFE_HOME, RIGHTSAFE_HOME, MIDDLESAFE_HOME, MOVE_COUNT};
const int maxFromId[MOVE_COUNT] =
               {4,4,4,4,
                2,2,3};
const int maxToId[MOVE_COUNT] =
               {4,2,2,3,
                4,4,4};

class myMap{
  public:
  myMap(){}
  myMap(const myMap& m);
  virtual ~myMap(){}
  int testAll(int depth=0, int minScore=-1, string track="");
  bool isValid(int moveId, int fromId, int toId);
  void makeMove(int moveId, int fromId, int toId);
  void output();
  char valToChar(int val);
  bool middleFree(int fromId, int toId);
  bool isDone();
  int leftSafe[2] = {-1, -1};
  int rightSafe[2] = {-1, -1};
  vector<int> home[4] = {{C, D, D, A}, {C, B, C, D}, {D, A, B, A}, {B, C, A, B}};
  int middleSafe[3] = {-1, -1, -1};
  int score=0;
};

class Day23
{
  public:
    Day23();
    virtual ~Day23();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY23_H
