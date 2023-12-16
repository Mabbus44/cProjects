#ifndef DAY10_H
#define DAY10_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

enum Dir {left, right, up, down};

class Move{
public:
  Move(){}
  Move(int x, int y, Dir d, int t) {posX = x; posY = y; dir = d; turn = t;}
  virtual ~Move(){}
  int posX;
  int posY;
  Dir dir;
  int turn;
  void output();
private:
};

struct Pos{
  int posX;
  int posY;
};

class Day10
{
  public:
    Day10();
    virtual ~Day10();
    void part1(string filename);
    void part2(string filename);
    void findStart();
    bool oneStep();
    bool isLastMoveValid();
    Dir opposite(Dir dir);
    int calcTurn(Dir inDir, Dir outDir);
    bool addEncircledPos(int posX, int posY);
    void addEncircledPositions(Move& m);

  protected:

  private:
    vector<vector<char>> _map;
    int _posX;
    int _posY;
    Dir _lastDir;
    int _steps;
    vector<Move> _moves;
    Dir _turnDir;
    vector<Pos> _encircledAreas;
};

#endif // DAY10_H
