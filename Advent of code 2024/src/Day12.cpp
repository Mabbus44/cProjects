#include "Day12.h"

Day12::Day12()
{
  //ctor
}

Day12::~Day12()
{
  //dtor
}

void Day12::part1(std::string filename){
  _fencedSquares.clear();
  InputLoader input(filename);
  _map = input.toVectorChar2d();
  int sum=0;
  for(int y=0; y<(int)_map.size(); y++){
    for(int x=0; x<(int)_map[0].size(); x++){
      if(!_fencedSquares.contains(Point2D(x, y))){
        _activeFence.clear();
        _activeFenceBorder = 0;
        _activeFenceChar = _map[y][x];
        addToActiveFence(Point2D(x, y));
        sum += _activeFenceBorder*_activeFence.size();
      }
    }
  }
  std::cout << "part 1: " << sum << std::endl;
}

void Day12::part2(std::string filename){
  _fencedSquares.clear();
  InputLoader input(filename);
  _map = input.toVectorChar2d();
  int sum=0;
  for(int y=0; y<(int)_map.size(); y++){
    for(int x=0; x<(int)_map[0].size(); x++){
      if(!_fencedSquares.contains(Point2D(x, y))){
        _activeFence.clear();
        _activeFenceBorder2.clear();
        _activeFenceChar = _map[y][x];
        addToActiveFence2(Point2D(x, y));
        sum += activeFenceSides()*_activeFence.size();
      }
    }
  }
  std::cout << "part 2: " << sum << std::endl;
}

char Day12::addToActiveFence(Point2D p){
  if(p.x < 0 || p.x >= (int)_map[0].size() || p.y < 0 || p.y >= (int)_map.size())
    return '-';
  if(_map[p.y][p.x] != _activeFenceChar)
    return _map[p.y][p.x];
  if(_activeFence.contains(p))
    return _activeFenceChar;
  _activeFence.insert(p);
  _fencedSquares.insert(p);
  if(addToActiveFence(Point2D(p.x+1, p.y)) != _activeFenceChar)
    _activeFenceBorder++;
  if(addToActiveFence(Point2D(p.x-1, p.y)) != _activeFenceChar)
    _activeFenceBorder++;
  if(addToActiveFence(Point2D(p.x, p.y+1)) != _activeFenceChar)
    _activeFenceBorder++;
  if(addToActiveFence(Point2D(p.x, p.y-1)) != _activeFenceChar)
    _activeFenceBorder++;
  return _activeFenceChar;
}

char Day12::addToActiveFence2(Point2D p){
  if(p.x < 0 || p.x >= (int)_map[0].size() || p.y < 0 || p.y >= (int)_map.size())
    return '-';
  if(_map[p.y][p.x] != _activeFenceChar)
    return _map[p.y][p.x];
  if(_activeFence.contains(p))
    return _activeFenceChar;
  _activeFence.insert(p);
  _fencedSquares.insert(p);
  if(addToActiveFence2(Point2D(p.x+1, p.y)) != _activeFenceChar)
    _activeFenceBorder2.insert(Point3D(p.x, p.y, Dir::RIGHT));
  if(addToActiveFence2(Point2D(p.x-1, p.y)) != _activeFenceChar)
    _activeFenceBorder2.insert(Point3D(p.x, p.y, Dir::LEFT));
  if(addToActiveFence2(Point2D(p.x, p.y+1)) != _activeFenceChar)
    _activeFenceBorder2.insert(Point3D(p.x, p.y, Dir::DOWN));
  if(addToActiveFence2(Point2D(p.x, p.y-1)) != _activeFenceChar)
    _activeFenceBorder2.insert(Point3D(p.x, p.y, Dir::UP));
  return _activeFenceChar;
}

int Day12::activeFenceSides(){
  int sideCount = 0;
  while(_activeFenceBorder2.begin() != _activeFenceBorder2.end()){
    sideCount++;
    removeActiveFenceSide(*_activeFenceBorder2.begin());
  }
  return sideCount;
}

void Day12::removeActiveFenceSide(Point3D p){
  if(_activeFenceBorder2.contains(p)){
    _activeFenceBorder2.erase(p);
    if(p.z == Dir::UP || p.z == Dir::DOWN){
      removeActiveFenceSide(Point3D(p.x+1, p.y, p.z));
      removeActiveFenceSide(Point3D(p.x-1, p.y, p.z));
    }else{
      removeActiveFenceSide(Point3D(p.x, p.y+1, p.z));
      removeActiveFenceSide(Point3D(p.x, p.y-1, p.z));
    }
  }
}
