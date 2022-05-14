#ifndef DAY14_H
#define DAY14_H
#include <iostream>
#include <vector>
#include "Common.h"

enum masks {ZERO, ONE, UNCHANGED};
const int FLOATING = 2;

class Mask
{
  public:
    Mask();
    Mask(string input);
    void load(string input);
    const vector<int>& bits() const {return _bits;}
    void output();
  private:
    vector<int> _bits;
};

class BinNum
{
  public:
    BinNum();
    BinNum(__int64 input);
    void load(__int64 input);
    void applyMask(Mask& m);
    vector<__int64> applyMask2(Mask& m);
    int len(){return _bits.size();}
    __int64 toInt();
    void getAllAddresses(vector<__int64>& addresses, int index, int depth, int maxDepth);
    void output();
    BinNum operator+(BinNum& other);
  private:
    vector<int> _bits;

};

class Day14
{
  public:
    Day14();
    virtual ~Day14();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY14_H
