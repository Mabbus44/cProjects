#ifndef DAY06_H
#define DAY06_H
#include "Common.h"
#include <set>

enum Dir {RIGHT, UP, LEFT, DOWN};

class Day06
{
  public:
    Day06();
    virtual ~Day06();
    void part1(std::string filename);
    void part2(std::string filename);
    int turnRight(int dir);
    void moveGuard();
    bool checkLoop();
    std::vector<std::vector<char>> room;
    int guardX=0;
    int guardY=0;
    int guardDir=Dir::RIGHT;
    int guardStartX=0;
    int guardStartY=0;
    int guardStartDir=Dir::RIGHT;
    bool leftRoom = false;
  protected:

  private:
};

#endif // DAY06_H
