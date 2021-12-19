#ifndef DAY18_H
#define DAY18_H
#include <iostream>
#include <vector>
#include "Common.h"

class SFNumber{
  public:
    SFNumber(){}
    SFNumber(SFNumber* p){parent = p;}
    virtual ~SFNumber(){}
    void load(string& input);
    void free();
    void output();
    void addLeft(int num);
    void addRight(int num);
    void addLeftOfMe(SFNumber* me, int num);
    void addRightOfMe(SFNumber* me, int num);
    bool explode(int level);
    bool split();
    int magnigude();
    SFNumber* add(SFNumber* other, bool output=false);
    SFNumber* parent = NULL;
    SFNumber* leftChild;
    SFNumber* rightChild;
    int val=-1;
};

class Day18
{
  public:
    Day18();
    virtual ~Day18();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY18_H
