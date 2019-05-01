#include "Functions.h"

int nextNumber(string line, unsigned int& index, bool first)
{
  if(index >= line.size())
    return 0;
  if(!first)
    while(index < line.size() && isNumber(line[index]))
      index++;
  while(index < line.size() && !isNumber(line[index]))
    index++;
  if(index >= line.size())
    return 0;
  return stoi(line.substr(index, line.size()-index));
}

bool isNumber(char letter)
{
  if(letter >=48 && letter <= 57)
    return true;
  return false;
}
