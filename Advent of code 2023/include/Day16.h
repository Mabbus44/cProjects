#ifndef DAY16_H
#define DAY16_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

enum Dir {up=0, down=1, left=2, right=3};

class Cell{
public:
  Cell();
  Cell(char c, int x, int y) : Cell() {_type = c; _x = x; _y = y;}
  virtual ~Cell(){}
  void connectNeighbours(Cell* newNeighbour, Dir neighbourDir);
  void evaluateRay(Dir incomingDir);
  bool isEnergized() {return _energized;}
  void reset();
  static Dir opositeDir(Dir dir);
private:
  char _type;
  Cell* _neighbours[4];
  bool _pathsCalculated[4];
  bool _energized = false;
  int _x;
  int _y;
};

class Day16
{
  public:
    Day16();
    virtual ~Day16();
    void part1(string filename);
    void part2(string filename);
    void loadGrid(string filename);
    void clearGrid();
    void resetCells();
    int energizedCount();

  protected:

  private:
    vector<vector<Cell*>> _grid;
};

#endif // DAY16_H
