#include "Day16.h"

Cell::Cell(){
  for(int i=0; i<4; i++){
    _neighbours[i] = nullptr;
    _pathsCalculated[i] = false;
  }
}

void Cell::reset(){
  for(int i=0; i<4; i++){
    _pathsCalculated[i] = false;
  }
  _energized = false;
}

void Cell::connectNeighbours(Cell* newNeighbour, Dir neighbourDir){
  _neighbours[neighbourDir] = newNeighbour;
  newNeighbour->_neighbours[opositeDir(neighbourDir)] = this;
}

void Cell::evaluateRay(Dir incomingDir){
  _energized = true;
  vector<Dir> ret;
  if(_type == '.'){
    ret = {incomingDir};
  }
  if(_type == '/'){
    if(incomingDir == Dir::right)
      ret = {Dir::up};
    if(incomingDir == Dir::left)
      ret = {Dir::down};
    if(incomingDir == Dir::down)
      ret = {Dir::left};
    if(incomingDir == Dir::up)
      ret = {Dir::right};
  }
  if(_type == '\\'){
    if(incomingDir == Dir::right)
      ret = {Dir::down};
    if(incomingDir == Dir::left)
      ret = {Dir::up};
    if(incomingDir == Dir::down)
      ret = {Dir::right};
    if(incomingDir == Dir::up)
      ret = {Dir::left};
  }
  if(_type == '|'){
    if(incomingDir == Dir::up || incomingDir == Dir::down)
      ret = {incomingDir};
    else
      ret = {Dir::up, Dir::down};
  }
  if(_type == '-'){
    if(incomingDir == Dir::left || incomingDir == Dir::right)
      ret = {incomingDir};
    else
      ret = {Dir::left, Dir::right};
  }
  for(Dir d: ret){
    if(!_pathsCalculated[d]){
      _pathsCalculated[d] = true;
      if(_neighbours[d] != nullptr)
        _neighbours[d]->evaluateRay(d);
    }
  }
}

Dir Cell::opositeDir(Dir dir){
  if(dir == Dir::left)
    return Dir::right;
  if(dir == Dir::right)
    return Dir::left;
  if(dir == Dir::up)
    return Dir::down;
  if(dir == Dir::down)
    return Dir::up;
  cout << "ERROR: Invalid dir in OpositeDir" << endl;
  return Dir::left;
}

Day16::Day16()
{
  //ctor
}

Day16::~Day16()
{
  //dtor
}

void Day16::part1(string filename){
  loadGrid(filename);
  _grid[0][0]->evaluateRay(Dir::right);
  cout << "part 1: " << energizedCount() << endl;
}

void Day16::part2(string filename){
  int maxEnergy = 0;
  loadGrid(filename);
  for(int y=0; y<(int)_grid.size(); y++){
    resetCells();
    _grid[y][0]->evaluateRay(Dir::right);
    int c = energizedCount();
    if(c > maxEnergy)
      maxEnergy = c;

    resetCells();
    _grid[y][_grid[0].size()-1]->evaluateRay(Dir::left);
    c = energizedCount();
    if(c > maxEnergy)
      maxEnergy = c;
  }
  for(int x=0; x<(int)_grid.size(); x++){
    resetCells();
    _grid[0][x]->evaluateRay(Dir::down);
    int c = energizedCount();
    if(c > maxEnergy)
      maxEnergy = c;

    resetCells();
    _grid[_grid.size()-1][x]->evaluateRay(Dir::up);
    c = energizedCount();
    if(c > maxEnergy)
      maxEnergy = c;
  }
  cout << "part 2: " << maxEnergy << endl;
}

void Day16::loadGrid(string filename){
  clearGrid();
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  for(int y = 0; y < (int)input.size(); y++){
    _grid.push_back(vector<Cell*>());
    for(int x = 0; x < (int)input[y].size(); x++){
      _grid[y].push_back(new Cell(input[y][x], x, y));
      if(y>0)
        _grid[y][x]->connectNeighbours(_grid[y-1][x], Dir::up);
      if(x>0)
        _grid[y][x]->connectNeighbours(_grid[y][x-1], Dir::left);
    }
  }
}

void Day16::clearGrid(){
  for(int y = 0; y < (int)_grid.size(); y++){
    for(int x = 0; x < (int)_grid[y].size(); x++){
      delete _grid[y][x];
    }
  }
  _grid.clear();
}

void Day16::resetCells(){
  for(int y = 0; y < (int)_grid.size(); y++){
    for(int x = 0; x < (int)_grid[y].size(); x++){
      _grid[y][x]->reset();
    }
  }
}

int Day16::energizedCount(){
  int ans = 0;
  for(int y = 0; y < (int)_grid.size(); y++){
    for(int x = 0; x < (int)_grid[y].size(); x++){
      if(_grid[y][x]->isEnergized())
        ans++;
    }
  }
  return ans;
}
