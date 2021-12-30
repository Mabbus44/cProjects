#include "Day12.h"

void Nav::load(string line){
  inst = line[0];
  val = stoi(line.substr(1, line.size()-1));
}

int Day12::charDirToInt(char dir){
  if(dir == 'N')
    return N;
  if(dir == 'E')
    return E;
  if(dir == 'S')
    return S;
  if(dir == 'W')
    return W;
  cout <<"Error dir" << endl;
  return -1;
}

void Day12::moveDir(int dir, int dist){
  switch(dir){
    case N:
      y += dist;
      break;
    case E:
      x += dist;
      break;
    case S:
      y -= dist;
      break;
    case W:
      x -= dist;
      break;
  }
}

void Day12::moveWPDir(int dir, int dist){
  switch(dir){
    case N:
      wpy += dist;
      break;
    case E:
      wpx += dist;
      break;
    case S:
      wpy -= dist;
      break;
    case W:
      wpx -= dist;
      break;
  }
}

void Day12::rotWP(int dist){
  while(dist<0)
    dist+=4;
  for(int i=0; i<dist; i++){
    int temp = wpy;
    wpy = -wpx;
    wpx = temp;
  }
}

void Day12::moveToWP(int dist){
  for(int i=0; i<dist; i++){
    x += wpx;
    y += wpy;
  }
}

Day12::Day12()
{
  //ctor
}

Day12::~Day12()
{
  //dtor
}

void Day12::part1(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  for(string line:vs){
    Nav i;
    i.load(line);
    instructions.push_back(i);
  }
  facingDirection = E;
  x=0;
  y=0;
  for(Nav i: instructions){
    if(i.inst == 'L'){
      facingDirection -= i.val/90;
      if(facingDirection<0)
        facingDirection += 4;
    }else if(i.inst == 'R'){
      facingDirection += i.val/90;
      if(facingDirection>=4)
        facingDirection -= 4;
    }else if(i.inst == 'F'){
      moveDir(facingDirection, i.val);
    }else{
      moveDir(charDirToInt(i.inst), i.val);
    }
  }
  cout << "part 1: " << abs(x)+abs(y) << endl;
}

void Day12::part2(string filename){
  instructions.clear();
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  for(string line:vs){
    Nav i;
    i.load(line);
    instructions.push_back(i);
  }
  x=0;
  y=0;
  wpx = 10;
  wpy = 1;
  for(Nav i: instructions){
    if(i.inst == 'L'){
      rotWP(-i.val/90);
    }else if(i.inst == 'R'){
      rotWP(i.val/90);
    }else if(i.inst == 'F'){
      moveToWP(i.val);
    }else{
      moveWPDir(charDirToInt(i.inst), i.val);
    }
  }
  cout << "part 2: " << abs(x)+abs(y) << endl;
}
