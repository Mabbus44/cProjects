#include "Day25.h"

Day25::Day25()
{
  //ctor
}

Day25::~Day25()
{
  //dtor
}

bool Day25::eastFree(int x, int y){
  if(x+1<sizeX)
    return cMap[y][x+1] == '.';
  return cMap[y][0] == '.';
}

bool Day25::southFree(int x, int y){
  if(y+1<sizeY)
    return cMap[y+1][x] == '.';
  return cMap[0][x] == '.';
}

void Day25::checkAllEast(){
  for(int y=0; y<sizeY; y++){
    for(int x=0; x<sizeX; x++){
      if(cMap[y][x] == '>'){
        canMove[y][x] = eastFree(x,y);
      }else if(cMap[y][x] == '.'){
        canMove[y][x] = false;
      }
    }
  }
}

void Day25::checkAllSouth(){
  for(int y=0; y<sizeY; y++){
    for(int x=0; x<sizeX; x++){
      if(cMap[y][x] == 'v'){
        canMove[y][x] = southFree(x,y);
      }else if(cMap[y][x] == '.'){
        canMove[y][x] = false;
      }
    }
  }
}

bool Day25::moveAllEast(){
  bool someoneMoved = false;
  for(int y=0; y<sizeY; y++){
    for(int x=0; x<sizeX; x++){
      if(cMap[y][x] == '>' && canMove[y][x]){
        someoneMoved = true;
        if(x+1<sizeX)
          cMap[y][x+1] = '>';
        else
          cMap[y][0] = '>';
        cMap[y][x] = '.';
      }
    }
  }
  return someoneMoved;
}

bool Day25::moveAllSouth(){
  bool someoneMoved = false;
  for(int y=0; y<sizeY; y++){
    for(int x=0; x<sizeX; x++){
      if(cMap[y][x] == 'v' && canMove[y][x]){
        someoneMoved = true;
        if(y+1<sizeY)
          cMap[y+1][x] = 'v';
        else
          cMap[0][x] = 'v';
        cMap[y][x] = '.';
      }
//        cout << "y: " << y << " x: " << x << " " << cMap[1][0] <<endl;
    }
  }
  return someoneMoved;
}

void Day25::output(){
  for(int y=0; y<sizeY; y++){
    for(int x=0; x<sizeX; x++){
      cout << cMap[y][x];
    }
    cout << endl;
  }
}

void Day25::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc=loader.toVectorChar2d();
  for(int y=0; y<sizeY; y++){
    for(int x=0; x<sizeX; x++){
      cMap[y][x] = vvc[y][x];
    }
  }
  int step=0;
  bool someoneMoved = true;
  while(someoneMoved){
    step++;
    someoneMoved = false;
    checkAllEast();
    if(moveAllEast())
      someoneMoved = true;
    checkAllSouth();
    if(moveAllSouth())
      someoneMoved = true;
  }
  cout << "Part 1: " << step <<endl;
}

void Day25::part2(string filename){
  InputLoader loader(filename);
  cout << "Part 2: "<<endl;
}
