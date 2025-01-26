#ifndef DAY12_H
#define DAY12_H
#include "Common.h"
#include <set>

enum Dir{UP, DOWN, LEFT, RIGHT};

class Day12
{
  public:
    Day12();
    virtual ~Day12();
    void part1(std::string filename);
    void part2(std::string filename);
    char addToActiveFence(Point2D p);
    char addToActiveFence2(Point2D p);
    int activeFenceSides();
    void removeActiveFenceSide(Point3D p);
  protected:

  private:
    std::vector<std::vector<char>> _map;
    std::set<Point2D> _fencedSquares;
    std::set<Point2D> _activeFence;
    int _activeFenceBorder;
    char _activeFenceChar;
    std::set<Point3D> _activeFenceBorder2;
};

#endif // DAY12_H
