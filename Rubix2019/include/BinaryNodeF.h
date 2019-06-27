#ifndef DIRECTIONS
enum DIRECTIONS {UP, DOWN, LEFT, RIGHT};
#define DIRECTIONS
#endif // DIRECTIONS

#ifndef BINARYNODEF_H
#define BINARYNODEF_H

#include "rubixCube20BF.h"
#include "FileHandler.h"

class FileHandler;

class BinaryNodeF
{
  public:
    __int64 adress;
    __int64 parent;
    __int64 smallerChild;
    __int64 biggerChild;
    __int64 height;
    BinaryNodeF();
    virtual ~BinaryNodeF();
    bool find(RubixCube20BF* other, FileHandler* fh);
    bool insert(RubixCube20BF* newCube, FileHandler* fh);
    bool rotUp(FileHandler* fh);
    void print(FileHandler* fh, bool verbose = false);

  protected:

  private:
};

#endif // BINARYNODEF_H
