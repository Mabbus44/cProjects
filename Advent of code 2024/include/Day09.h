#ifndef DAY09_H
#define DAY09_H
#include "Common.h"
#include <list>

class Day09
{
  public:
    Day09();
    virtual ~Day09();
    void part1(std::string filename);
    void part2(std::string filename);
    int firstEmpyBlock(std::vector<int>& blocks, int startId);
    void swapBlocks(std::vector<int>& blocks, int idA, int idB);
    std::list<Point2D>::iterator firstSpotWhereBlockFits(std::list<Point2D>& blocks, std::list<Point2D>::iterator fitBlock);
    bool insertBlockAtIt(std::list<Point2D>& blocks, std::list<Point2D>::iterator insertAt, std::list<Point2D>::iterator insertBlock);
    __int64 checksumForBlock(Point2D block, int firstId);
  protected:

  private:
};

#endif // DAY09_H
