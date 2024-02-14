#ifndef DAY18_H
#define DAY18_H
#include <iostream>
#include <vector>
#include "Common.h"
#include <tuple>
#include <deque>

using namespace std;

enum Dir{right = 0,down = 1,left = 2,up = 3};

class Square{
public:
  Square();
  virtual ~Square(){}
  void output();
  void dig(string color, bool edge = true);
  void checked(bool c) {_checked = c;}
  bool checked() {return _checked;}
  void dug(bool d) {_dug = d;}
  bool dug() {return _dug;}

private:
  string _color;
  bool _dug;
  bool _edge;
  bool _checked;
};

class Instruction{
public:
  Instruction(){}
  Instruction(string input){load(input);}
  virtual ~Instruction(){}
  void load(string hex);
  Dir dir(){return _dir;}
  void swapDir(bool s){_swapDir = s;}
  int length(){return _length;}
private:
  Dir _dir;
  bool _swapDir;
  int _length;
};

class Line{
public:
  Line(){}
  Line(int start, int stop, bool swapDir){ _startX = start; _stopX = stop, _swapDir = swapDir;}
  virtual ~Line(){}
private:
  int _startX;
  int _stopX;
  bool _swapDir;
};

class Segment{
public:
  Segment(){}
  Segment(Line line){_lines.push_back(line); _startY}
  virtual ~Segment(){}
private:
  vector<Line> _lines;
  int _startY;
  int _stopY;
};

class Day18
{
  public:
    Day18();
    virtual ~Day18();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
    void resetGround();
    void digMany(string dir, int len, string color);
    void digOne(int x, int y, string color);
    void addLineLeft();
    void addLineRight();
    void addLineUp();
    void addLineDown();
    void output(int part);
    void checkSquare(int x, int y, int depth=0);
    void digAllUnchecked();
    int countHoles();
    int _minX;
    int _minY;
    int _posX;
    int _posY;
    vector<vector<Square*>> _ground;
};

#endif // DAY18_H
