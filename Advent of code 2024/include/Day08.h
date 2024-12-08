#ifndef DAY08_H
#define DAY08_H
#include "Common.h"
#include <set>

class Day08
{
  public:
    Day08();
    virtual ~Day08();
    void part1(std::string filename);
    void part2(std::string filename);

  protected:

  private:
};

class AntennaFamily{
  public:
    AntennaFamily() {}
    AntennaFamily(char f, Point2D p) {family = f; antennas.insert(p);}
    void addAntiNodes(std::set<Point2D>& antiNodes, int mapSizeX, int mapSizeY);
    void addAntiNodes2(std::set<Point2D>& antiNodes, int mapSizeX, int mapSizeY);
    virtual ~AntennaFamily(){}
    char family='.';
    std::set<Point2D> antennas;
};

#endif // DAY08_H
