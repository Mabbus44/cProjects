#ifndef DAY10_H
#define DAY10_H
#include "Common.h"
#include <set>

class Day10
{
  public:
    Day10();
    virtual ~Day10();
    void part1(std::string filename);
    void part2(std::string filename);
    void loadMap(std::string filename);
    void outputMap();
    std::set<Point2D> getPaths(int x, int y, int findNum);
    int getPaths2(int x, int y, int findNum);
    std::vector<std::vector<int>> typoMap;
  protected:

  private:
};

#endif // DAY10_H
