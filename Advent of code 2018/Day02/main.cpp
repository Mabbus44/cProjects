#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

bool exactlyX(string line, int x);
char differingLetter(string line1, string line2);
string removeChar(string line, char letter);

int main()
{
  ifstream input;
  string line;
  list<string> inputList;
  int countTwo = 0;
  int countThree = 0;
  string ans2;

  input.open("C:\\Users\\rasun\\Documents\\C++ Projects\\Advent of code 2018\\Input\\Day02.txt");
  while(getline(input, line))
    inputList.push_back(line);
  input.close();
  for(list<string>::iterator it = inputList.begin(); it != inputList.end(); ++it)
  {
    if(exactlyX(*it, 2))
      countTwo++;
    if(exactlyX(*it, 3))
      countThree++;
    for(list<string>::iterator it2 = inputList.begin(); it2 != inputList.end(); ++it2)
    {
      char letter = differingLetter(*it, *it2);
      if(letter != 0)
        ans2 = removeChar(*it, letter);
    }
  }
  cout << "Part 1:" << countTwo*countThree << endl;
  cout << "Part 2:" << ans2;
  return 0;
}

bool exactlyX(string line, int x)
{
  int matches;
  for(unsigned int i=0; i<line.size(); i++)
  {
    matches = 1;
    for(unsigned int i2=0; i2<line.size(); i2++)
      if(i != i2 && line[i] == line[i2])
        matches++;
    if(matches == x)
      return true;
  }
  return false;
}

char differingLetter(string line1, string line2)
{
  int differCount = 0;
  char differChar = 0;
  if(line1.size() != line2.size())
    return 0;
  for(unsigned int i=0; i<line1.size(); i++)
  {
    if(line1[i] != line2[i])
    {
      differCount++;
      differChar = line1[i];
    }
    if(differCount>1)
      return 0;
  }
  return differChar;
}

string removeChar(string line, char letter)
{
  int pos = line.find(letter);
  line.erase(pos, 1);
  return line;
}
