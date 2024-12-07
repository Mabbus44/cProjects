#ifndef DAY07_H
#define DAY07_H
#include "Common.h"

class Day07
{
  public:
    Day07();
    virtual ~Day07();
    void part1(std::string filename);
    void part2(std::string filename);
    bool canSolve(std::vector<__int64>& row, int id, __int64 sum);
    bool canSolve2(std::vector<__int64>& row, int id, __int64 sum);
    __int64 concatenate(__int64 a, __int64 b);
  protected:

  private:
};

#endif // DAY07_H
