#ifndef DAY05_H
#define DAY05_H
#include <iostream>
#include <vector>
#include "Common.h"

class Line{
  public:
    Line(){};
    Line(const Line &l){x1=l.x1; y1=l.y1; x2=l.x2; y2=l.y2;}
    ~Line(){};
    void loadInput(vector<int> input);
    void output();
    int x1, y1, x2, y2;
};

class Grid{
  public:
    Grid(){};
    ~Grid(){};
    void init(int gridSize);
    void setGrid(vector<Line>& lines, bool countDiagonal=false);
    int getIntersections();
    void output();
    int gridSize;
    vector<vector<int>> grid;
};

class Day05
{
  public:
    Day05();
    virtual ~Day05();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY05_H
