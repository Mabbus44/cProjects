/*#ifndef BINARYNODEF_H
#define BINARYNODEF_H
#include "RubixCube20BF.h"

class BinaryNodeF
{
  public:
    int cubeAdress;
    int parent;
    int smallerChild;
    int biggerChild;
    int height;
    BinaryNodeF();
    virtual ~BinaryNodeF();
    bool find(RubixCube20BF* other);
    bool insert(RubixCube20BF* newCube);
    bool rotUp();
    void print(bool verbose = false);

  protected:

  private:
};

#endif // BINARYNODEF_H
*/
