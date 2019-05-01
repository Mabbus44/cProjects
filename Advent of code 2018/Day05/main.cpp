#include <iostream>
#include <fstream>
#include <string>
#include "Polymer.h"

using namespace std;

int main()
{
  ifstream input;
  string line;
  Polymer p;
  int smallestSize = -1;
  char removedLetter;

  input.open("C:\\Users\\rasun\\Documents\\C++ Projects\\Advent of code 2018\\Input\\Day05.txt");
  getline(input, line);
  input.close();
  p.line = line;
  p.reduce();
  cout << "Part 1: " << p.line.size() << endl;
  for(char c=65; c<91; c++)
  {
    p.line = line;
    p.remove(c);
    p.remove(c+32);
    p.reduce();
    if(p.line.size()<smallestSize || smallestSize == -1)
    {
      smallestSize = p.line.size();
      removedLetter = c;
    }
  }
  cout << "Part 2: " << smallestSize << " (removed letters: " << removedLetter << "/" << (char)(removedLetter+32) << ")" << endl;
}
