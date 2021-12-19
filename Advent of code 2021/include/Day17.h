#ifndef DAY17_H
#define DAY17_H
#include <iostream>
#include <vector>
#include "Common.h"

enum hit {UNDERSHOOT, STILL_POSSIBLE, HIT, OVERSHOOT, UNKNOWN_MISS};

class Day17
{
  public:
    Day17();
    virtual ~Day17();
    void part1(string filename);
    void part2(string filename);
    int hitTarget();
    void shoot(int px, int py) {x=0, y=0, speedX=px; speedY=py;}
    void travel();
    int x,y,speedX, speedY;
    int targetXMin=14;
    int targetXMax=50;
    int targetYMin=-267;
    int targetYMax=-225;
    /*int targetXMin=20;
    int targetXMax=30;
    int targetYMin=-10;
    int targetYMax=-5;*/
  protected:

  private:
};

#endif // DAY17_H
