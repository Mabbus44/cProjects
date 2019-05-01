#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int lineToInt(string& line);

int main()
{
  ifstream input;
  string line;
  __int64 sum = 0;
  list<int> inputList;
  list<__int64> sumList;
  bool matchFound = false;

  input.open("C:\\Users\\rasun\\Documents\\C++ Projects\\Advent of code 2018\\Input\\Day01.txt");
  while(getline(input, line))
    inputList.push_back(lineToInt(line));
  input.close();
  for(list<int>::iterator it = inputList.begin(); it != inputList.end(); ++it)
    sum += *it;
  cout << "Part 1:" << sum << endl;
  sum = 0;

  sumList.push_back(0);
  while(!matchFound)
  {
    for(list<int>::iterator it = inputList.begin(); it != inputList.end() && !matchFound; ++it)
    {
      sum += *it;
      for(list<__int64>::iterator it2 = sumList.begin(); it2 != sumList.end() && !matchFound; ++it2)
      {
        if(sum == *it2)
          matchFound = true;
      }
      sumList.push_back(sum);
    }
  }
  cout << "Part 2:" << sum << endl;
  return 0;
}

int lineToInt(string& line)
{
  int sign = 0;
  int ret = 0;
  bool signChar = false;
  bool invalidChar = false;
  for(unsigned int i=0; i<line.size() && !invalidChar; i++)
  {
    signChar = false;
    if(sign == 0)
    {
      if(line[i] == '+')
      {
        sign = 1;
        signChar = true;
      }
      if(line[i] == '-')
      {
        sign = -1;
        signChar = true;
      }
      if(int(line[i]) >= 48 && int(line[i]) <= 57)
        sign = 1;
      if(sign == 0)
        return 0;
    }
    if(!signChar)
    {
      if(int(line[i]) >= 48 && int(line[i]) <= 57)
        ret = 10*ret + int(line[i])-48;
      else
        invalidChar = true;
    }
  }
  return ret*sign;
}
