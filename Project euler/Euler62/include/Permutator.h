#ifndef PERMUTATOR_H
#define PERMUTATOR_H
#include <list>
#include "Btree.h"

using namespace std;

class Permutator
{
  public:
    Permutator();
    void populateCubes(__int64 upTo);
    void findLowestCube(int permCount);

  protected:

  private:
    bool debug;
    Btree cubes;
    __int64 number;
    __int64 biggestCube;
    bool fail;
    list<int> digits;
    list<int> digitsPerm;
    list<__int64> cubePerms;
    void separateDigits();
    void permute(list<int>& digits);
    bool checkCube();
};

#endif // PERMUTATOR_H
