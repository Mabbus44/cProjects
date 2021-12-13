#ifndef DAY13_H
#define DAY13_H
#include <iostream>
#include <vector>
#include "Common.h"

enum directions {X, Y};

class Coord{
public:
  Coord(){};
  Coord(const Coord& other){x=other.x; y=other.y;}
  Coord(int x, int y){this->x=x; this->y=y;}
  bool operator==(const Coord& other){return x==other.x && y==other.y;}
  virtual ~Coord(){}
  int x=-9999999;
  int y=-9999999;
};

class Instruction{
public:
  Instruction(){};
  Instruction(const Instruction& other){dir=other.dir; row=other.row;}
  Instruction(int dir, int row){this->dir=dir; this->row=row;}
  virtual ~Instruction(){}
  int dir=-9999999;
  int row=-9999999;
};

class Day13
{
  public:
    Day13();
    virtual ~Day13();
    void loadInput(string fileName);
    void part1(string filename);
    void part2(string filename);
    void removeDuplicateDots();
    void fold(Instruction inst);
    vector<Coord> coords;
    vector<Instruction> instructions;
  protected:

  private:
};

#endif // DAY13_H
