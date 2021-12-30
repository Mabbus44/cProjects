#ifndef DAY08_H
#define DAY08_H
#include <iostream>
#include <vector>
#include "Common.h"

enum instructions {NOP, ACC, JMP};

class Instruction{
public:
  Instruction(){};
  Instruction(int i, int v, bool r=false){instruction=i; val=v; run=r;}
  virtual ~Instruction(){};
  void output();
  int instruction;
  int val;
  bool run;
};

class Day08
{
  public:
    Day08();
    virtual ~Day08();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY08_H
