#include "Day03.h"

Day03::Day03()
{
  //ctor
}

Day03::~Day03()
{
  //dtor
}

void Day03::move(int x, int y){
  posX += x;
  posY += y;
  if(posX>=(int)treeMap[0].size())
    posX-=(int)treeMap[0].size();
}

void Day03::part1(string filename){
  InputLoader loader(filename);
  treeMap = loader.toVectorChar2d();
  posX=0;
  posY=0;
  int count=0;
  while(posY<(int)treeMap.size()){
    if(treeMap[posY][posX]=='#')
      count++;
    move(3,1);
  }
  cout << "part 1: " << count << endl;
}

void Day03::part2(string filename){
  InputLoader loader(filename);
  treeMap = loader.toVectorChar2d();
  posX=0;
  posY=0;
  int64_t product=1;
  int64_t count;
  count=0;
  while(posY<(int)treeMap.size()){
    if(treeMap[posY][posX]=='#')
      count++;
    move(1,1);
  }
  product *= count;
  posX=0;
  posY=0;
  count=0;
  while(posY<(int)treeMap.size()){
    if(treeMap[posY][posX]=='#')
      count++;
    move(3,1);
  }
  product *= count;
  posX=0;
  posY=0;
  count=0;
  while(posY<(int)treeMap.size()){
    if(treeMap[posY][posX]=='#')
      count++;
    move(5,1);
  }
  product *= count;
  posX=0;
  posY=0;
  count=0;
  while(posY<(int)treeMap.size()){
    if(treeMap[posY][posX]=='#')
      count++;
    move(7,1);
  }
  product *= count;
  posX=0;
  posY=0;
  count=0;
  while(posY<(int)treeMap.size()){
    if(treeMap[posY][posX]=='#')
      count++;
    move(1,2);
  }
  product *= count;
  cout << "part 2: " << product << endl;
}
