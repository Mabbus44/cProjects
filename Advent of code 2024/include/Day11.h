#ifndef DAY11_H
#define DAY11_H
#include "Common.h"
#include <list>
#include <map>
#include <unordered_set>

class BlinkNum
{
  public:
    BlinkNum(){}
    BlinkNum(int b, __int64 n){blink = b; num = n;}
    virtual ~BlinkNum(){}
    int blink;
    __int64 num;
};

class Day11
{
  public:
    Day11();
    virtual ~Day11();
    void part1(std::string filename);
    void part2(std::string filename);
    void operate(std::list<__int64>::iterator numIt);
    int digitCount(__int64 num);
    std::list<__int64> numbers;
    void addToNewState(__int64 num, __int64 count);
  protected:

  private:
    std::map<__int64, __int64> _oldState;
    std::map<__int64, __int64> _newState;
};



#endif // DAY11_H
