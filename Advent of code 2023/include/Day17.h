#ifndef DAY17_H
#define DAY17_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

namespace day17{

  enum Dir {up=0, down=1, left=2, right=3};

  class Cell{
  public:
    Cell();
    Cell(int hl, int x, int y, int* i) : Cell() {_heatLoss = hl; _x = x; _y = y; _bestFinnish = i;}
    virtual ~Cell(){}
    void connectNeighbours(Cell* newNeighbour, Dir neighbourDir);
    void evaluateCart(Dir incomingDir, int heatLoss, int travelDist, bool dontAddHeatloss = false);
    void evaluateCart2(Dir incomingDir, int heatLoss, int travelDist, bool dontAddHeatloss = false);
    int calcTravelDist(Dir incomingDir, Dir outgoingDir, int travelDist, bool noIncomingDir = false);
    static Dir opositeDir(Dir dir);
    void finalCell(bool b){_finalCell = b;}
    void output(string tab = "");
    Cell* neighbour(Dir d) {return _neighbours[d];}
    Cell* myAddr() {return this;}
  private:
    int _heatLoss;
    Cell* _neighbours[4];
    int* _bestFinnish;
    int _bestArrival[4][10]; //[Dir][TravelDist]
    int _x;
    int _y;
    bool _finalCell;
  };

  class Day17
  {
    public:
      Day17();
      virtual ~Day17();
      void part1(string filename);
      void part2(string filename);

    protected:

    private:
  };
}
#endif // DAY17_H
