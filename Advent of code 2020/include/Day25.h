#ifndef DAY25_H
#define DAY25_H
#include <iostream>
#include <vector>
#include "Common.h"


class Day25
{
  public:
    Day25();
    virtual ~Day25();
    void part1(string filename);
    void part2(string filename);
    __int64 tform(__int64 subject, __int64 loop);
    __int64 findLoop(__int64 subject, __int64 target);

  protected:

  private:
};

#endif // DAY25_H
