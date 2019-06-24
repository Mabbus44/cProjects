#ifndef SEB
enum SEB {SMALLER, EQUALS, BIGGER};
#define SEB
#endif // SEB

#ifndef RUBIXCUBE_H
#define RUBIXCUBE_H

#include <inttypes.h>

class RubixCube
{
  public:
    __int8 colors[6][8];
    RubixCube* parent;
    RubixCube* firstChild;
    RubixCube* sibling;

    RubixCube();
    RubixCube& operator=(const RubixCube& other);
    bool operator==(const RubixCube& other);
    bool operator<(const RubixCube& other);
    bool operator>(const RubixCube& other);
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

class CubeContainer
{
  public:
    RubixCube* cube;

    CubeContainer();
    CubeContainer& operator=(const RubixCube& other);
    CubeContainer& operator=(const CubeContainer& other);
    bool operator==(const CubeContainer& other);
    bool operator<(const CubeContainer& other) const;
    bool operator>(const CubeContainer& other) const;
    virtual ~CubeContainer();

  protected:
  private:
};

#endif // RUBIXCUBE_H
