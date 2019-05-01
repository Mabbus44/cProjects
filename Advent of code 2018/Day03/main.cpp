#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Claim.h"
#include "Functions.h"

using namespace std;

int main()
{
  ifstream input;
  string line;
  list<string> inputList;
  list<Claim> claimList;
  int maxX = 0;
  int maxY = 0;
  int overlapCount = 0;
  bool noOverlap;
  int noOverlapID = 0;

  input.open("C:\\Users\\rasun\\Documents\\C++ Projects\\Advent of code 2018\\Input\\Day03.txt");
  while(getline(input, line))
    inputList.push_back(line);
  input.close();
  for(list<string>::iterator it = inputList.begin(); it != inputList.end(); ++it)
  {
    Claim c(*it);
    claimList.push_back(c);
    if(c.posX+c.sizeX > maxX)
      maxX = c.posX+c.sizeX;
    if(c.posY+c.sizeY > maxY)
      maxY = c.posY+c.sizeY;
  }
  int** matrix;
  matrix = new int*[maxX];

  for(int x=0; x<maxX; x++)
  {
    matrix[x] = new int[maxY];
    for(int y=0; y<maxY; y++)
      matrix[x][y] = 0;
  }
  for(list<Claim>::iterator it = claimList.begin(); it != claimList.end(); ++it)
    for(int y=it->posY; y<it->posY+it->sizeY; y++)
      for(int x=it->posX; x<it->posX+it->sizeX; x++)
        matrix[x][y]++;
  for(int y=0; y<maxY; y++)
    for(int x=0; x<maxX; x++)
      if(matrix[x][y] > 1)
        overlapCount++;
  for(list<Claim>::iterator it = claimList.begin(); it != claimList.end(); ++it)
  {
    noOverlap = true;
    for(int y=it->posY; y<it->posY+it->sizeY; y++)
      for(int x=it->posX; x<it->posX+it->sizeX; x++)
        if(matrix[x][y] > 1)
          noOverlap = false;
    if(noOverlap)
      noOverlapID = it->id;
  }
  cout << "Part 1:" << overlapCount << endl;
  cout << "Part 2:" << noOverlapID << endl;
  return 0;
}
