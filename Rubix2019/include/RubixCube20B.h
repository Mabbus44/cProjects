#ifndef RUBIXCUBE20B_H
#define RUBIXCUBE20B_H


class RubixCube20B
{
  public:
    __int8 corners[8];
    __int8 sides[12];
    RubixCube20B* parent;
    RubixCube20B* firstChild;
    RubixCube20B* sibling;

    RubixCube20B();
    RubixCube20B& operator=(const RubixCube20B& other);
    bool operator==(const RubixCube20B& other);
    bool operator<(const RubixCube20B& other);
    bool operator>(const RubixCube20B& other);
    void print();
    RubixCube20B returnChild(int move);
    RubixCube20B returnRot(int rot);
    void setSide(int side, RubixCube20B* other, int otherSide);
    void setSideRotLeft(int side, RubixCube20B* other, int otherSide);
    void setSideRotRight(int side, RubixCube20B* other, int otherSide);
    void setSideRotX(int side, RubixCube20B* other, int otherSide);
    void swapNumber(int a, int b);
    void swapNumber(int a, int b, int c);
    void swapNumber(int a, int b, int c, int d);
    virtual ~RubixCube20B();

  protected:

  private:
};

class CubeContainer20B
{
  public:
    RubixCube20B* cube;

    CubeContainer20B();
    CubeContainer20B& operator=(const RubixCube20B& other);
    CubeContainer20B& operator=(const CubeContainer20B& other);
    bool operator==(const CubeContainer20B& other);
    bool operator<(const CubeContainer20B& other) const;
    bool operator>(const CubeContainer20B& other) const;
    virtual ~CubeContainer20B();

  protected:
  private:
};

#endif // RUBIXCUBE20B_H
