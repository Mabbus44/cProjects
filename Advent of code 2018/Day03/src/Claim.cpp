#include "Claim.h"

Claim::Claim()
{
  //ctor
}

Claim::Claim(string line)
{
  loadData(line);
}

Claim::~Claim()
{
  //dtor
}

void Claim::loadData(string line)
{
  unsigned int index = 0;
  id = nextNumber(line, index, true);
  posX = nextNumber(line, index);
  posY = nextNumber(line, index);
  sizeX = nextNumber(line, index);
  sizeY = nextNumber(line, index);
}

void Claim::output()
{
  cout << "ID: " << id << endl;
  cout << "Pos: " << posX << ", " << posY << endl;
  cout << "Size: " << sizeX << ", " << sizeY << endl;
}
