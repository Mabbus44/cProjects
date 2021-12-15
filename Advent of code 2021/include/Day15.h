#ifndef DAY15_H
#define DAY15_H
#include <iostream>
#include <vector>
#include "Common.h"

class Room{
public:
  Room(){}
  virtual ~Room(){}
  int risk;
  int lowestRisk;
  bool lowestRiskCalculated=false;
};

class Day15
{
  public:
    Day15();
    virtual ~Day15();
    void part1(string filename);
    void part2(string filename);
    void crawl(int y, int x, int sum);
    void crawlPart2(int y, int x, int sum);
    void drawLowestRisk();
    void setLowestRisk(int y, int x);
    void setLowestRiskPart2(int y, int x);
    Room rooms[100][100];
    int lowestRisk[500][500];
    bool lowestRiskCalculated[500][500];
    int getRisk(int y, int x);
    int debugX;
    int debugY;
  protected:

  private:
};

#endif // DAY15_H
