#ifndef DAY08_H
#define DAY08_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Day08
{
  public:
    Day08();
    virtual ~Day08();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

class Tree
{
  public:
    Tree(){}
    Tree(int h, int x, int y){height = h; this->x = x; this->y = y;}
    virtual ~Tree(){}
    bool isVisible(){return height>highestW || height>highestE || height>highestS || height>highestN;}
    int score(){return viewDistanceW*viewDistanceE*viewDistanceS*viewDistanceN;}
    int height;
    int highestW=-1;
    int highestE=-1;
    int highestS=-1;
    int highestN=-1;
    int viewDistanceW;
    int viewDistanceE;
    int viewDistanceS;
    int viewDistanceN;
    int x;
    int y;
};
#endif // DAY08_H
