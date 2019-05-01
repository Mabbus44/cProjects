#include "Polymer.h"

Polymer::Polymer()
{
  //ctor
}

Polymer::~Polymer()
{
  //dtor
}

Polymer::Polymer(string line)
{
  this->line = line;
}

void Polymer::reduce()
{
  for(int i=0; (unsigned int)i<line.size()-1; i++)
  {
    if(line[i] == line[i+1] + 32 || line[i] == line[i+1] - 32)
    {
      line.erase(i, 2);
      i-=2;
      if(i<=-2)
        i=-1;
    }
  }
}

void Polymer::remove(char r)
{
  for(int i=0; (unsigned int)i<line.size(); i++)
  {
    if(line[i] == r)
    {
      line.erase(i, 1);
      i--;
    }
  }
}
