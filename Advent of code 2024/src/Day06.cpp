#include "Day06.h"

Day06::Day06()
{
  //ctor
}

Day06::~Day06()
{
  //dtor
}

void Day06::part1(std::string filename){
  InputLoader loader(filename);
  room = loader.toVectorChar2d();
  for(int y=0; y<(int)room.size(); y++){
    for(int x=0; x<(int)room[0].size(); x++){
      if(room[y][x] == '>'){
        guardX = x;
        guardY = y;
        guardDir = Dir::RIGHT;
      }
      if(room[y][x] == '^'){
        guardX = x;
        guardY = y;
        guardDir = Dir::UP;
      }
      if(room[y][x] == '<'){
        guardX = x;
        guardY = y;
        guardDir = Dir::LEFT;
      }
      if(room[y][x] == 'v'){
        guardX = x;
        guardY = y;
        guardDir = Dir::DOWN;
      }
    }
  }
  std::set<Point2D> visitedPoints;
  visitedPoints.insert(Point2D(guardX, guardY));
  while(!leftRoom){
    moveGuard();
    visitedPoints.insert(Point2D(guardX, guardY));
  }
  std::cout << "part 1: " << visitedPoints.size() << std::endl;
}

void Day06::part2(std::string filename){
  InputLoader loader(filename);
  room = loader.toVectorChar2d();
  for(int y=0; y<(int)room.size(); y++){
    for(int x=0; x<(int)room[0].size(); x++){
      if(room[y][x] == '>'){
        guardStartX = x;
        guardStartY = y;
        guardStartDir = Dir::RIGHT;
      }
      if(room[y][x] == '^'){
        guardStartX = x;
        guardStartY = y;
        guardStartDir = Dir::UP;
      }
      if(room[y][x] == '<'){
        guardStartX = x;
        guardStartY = y;
        guardStartDir = Dir::LEFT;
      }
      if(room[y][x] == 'v'){
        guardStartX = x;
        guardStartY = y;
        guardStartDir = Dir::DOWN;
      }
    }
  }
  int loopCount = 0;
  for(int y=0; y<(int)room.size(); y++){
    for(int x=0; x<(int)room[0].size(); x++){
      if(room[y][x] == '.'){
        room[y][x] = '#';
        guardX = guardStartX;
        guardY = guardStartY;
        guardDir = guardStartDir;
        leftRoom = false;
        if(checkLoop())
          loopCount++;
        room[y][x] = '.';
      }
    }
  }
  std::cout << "part 2: " << loopCount << std::endl;}

int Day06::turnRight(int dir){
  switch(dir){
    case Dir::RIGHT:
      return Dir::DOWN;
    case Dir::UP:
      return Dir::RIGHT;
    case Dir::LEFT:
      return Dir::UP;
    case Dir::DOWN:
      return Dir::LEFT;
  }
  std::cout << "Error: Invalid dir " << dir << " in turnright()" << std::endl;
  return -1;
}

void Day06::moveGuard(){
  int newX = guardX;
  int newY = guardY;
  switch(guardDir){
    case Dir::RIGHT:
      newX = guardX+1;
      break;
    case Dir::UP:
      newY = guardY-1;
      break;
    case Dir::LEFT:
      newX = guardX-1;
      break;
    case Dir::DOWN:
      newY = guardY+1;
      break;
    default:
      std::cout << "Error: Invalid dir " << guardDir << " in moveGuard()" << std::endl;
      return;
  }
  if(newX < 0 || newX >= (int)room[0].size() || newY < 0 || newY >= (int)room.size()){
    leftRoom = true;
    return;
  }
  if(room[newY][newX] == '#'){
    guardDir = turnRight(guardDir);
    return;
  }
  guardX = newX;
  guardY = newY;
}

bool Day06::checkLoop(){
  std::set<Point3D> visited;
  Point3D stdartPointAndDir(guardX, guardY, guardDir);
  visited.insert(stdartPointAndDir);
  while(!leftRoom){
    moveGuard();
    Point3D pointAndDir(guardX, guardY, guardDir);
    if(!leftRoom && visited.contains(pointAndDir)){
      return true;
    }
    visited.insert(pointAndDir);
  }
  return false;
}
