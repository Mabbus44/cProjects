#ifndef SEB
enum SEB {SMALLER, EQUALS, BIGGER};
#define SEB
#endif // SEB

#ifndef RUBIXCUBE20BF_H
#define RUBIXCUBE20BF_H
#include <iomanip>


class RubixCube20BF
{
  public:
    __int8 corners[8];
    __int8 sides[12];
    __int64 adress;
    __int64 parent;
    __int64 firstChild;
    __int64 sibling;

    RubixCube20BF();
    RubixCube20BF& operator=(const RubixCube20BF& other);
    bool operator==(const RubixCube20BF& other);
    bool operator<(const RubixCube20BF& other);
    bool operator>(const RubixCube20BF& other);
    int seb(RubixCube20BF* other);
    void print(bool verbose = false);
    RubixCube20BF returnChild(int move);
    RubixCube20BF returnRot(int rot);
    __int8 turnSide(__int8 side);
    __int8 turnCornerRight(__int8 corner);
    __int8 turnCornerLeft(__int8 corner);
    __int8 replaceSide(__int8 side, int rot);
    __int8 replaceCorner(__int8 corner, int rot);
    virtual ~RubixCube20BF();

  protected:

  private:
};

#endif // RUBIXCUBE20BF_H

