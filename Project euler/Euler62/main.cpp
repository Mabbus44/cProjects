#include <iostream>
#include "Permutator.h"

using namespace std;

int main()
{
  Permutator p;
  p.populateCubes(2000000000000);
  p.findLowestCube(5);
  return 0;
}
