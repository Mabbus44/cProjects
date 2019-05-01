#ifndef RUBIXCUBE_H
#define RUBIXCUBE_H

#include <inttypes.h>

class RubixCube
{
  public:
    __int8 colors[6][8];
    RubixCube* parent;

    RubixCube();
    RubixCube& operator=(const RubixCube& other);
    bool operator==(const RubixCube& other);
    void print();
    RubixCube returnChild(int move);
    RubixCube returnRot(int rot);
    void setSide(int side, RubixCube* other, int otherSide);
    void setSideRotLeft(int side, RubixCube* other, int otherSide);
    void setSideRotRight(int side, RubixCube* other, int otherSide);
    void setSideRotX(int side, RubixCube* other, int otherSide);
    void swapNumber(int a, int b);
    void swapNumber(int a, int b, int c);
    void swapNumber(int a, int b, int c, int d);
    virtual ~RubixCube();

  protected:

  private:
};

#endif // RUBIXCUBE_H
