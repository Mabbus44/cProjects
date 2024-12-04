#ifndef DAY04_H
#define DAY04_H
#include "Common.h"

class Day04
{
  public:
    Day04();
    virtual ~Day04();
    void part1(std::string filename);
    void part2(std::string filename);
    bool findXmas(int x, int y, int dX, int dY);
    bool findXdashMas(int x, int y);
    std::vector<std::vector<char>> input;
  protected:

  private:
};

#endif // DAY04_H
