#include "Day11.h"

Day11::Day11()
{
  //ctor
}

Day11::~Day11()
{
  //dtor
}

void Day11::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  Universe u;
  u.map(input);
  u.expandUniverse();
  u.setGalaxies();
  cout << "part 1: " << u.galaxyDistances() << endl;
}

void Day11::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  Universe u;
  u.map(input);
  u.setEmptyLines();
  u.setGalaxies();
  cout << "part 2: " << u.galaxyDistancesWithEmptyLines() << endl;
}

void Universe::expandUniverse(){
  for(int row=0; row < (int)_map.size(); row++){
    bool empty = true;
    for(int col=0; col < (int)_map[0].size() && empty; col++){
      if(_map[row][col] == '#')
        empty = false;
    }
    if(empty){
      _map.insert(_map.begin() + row, vector<char>(_map[0].size(), '.'));
      row++;
    }
  }
  for(int col=0; col < (int)_map[0].size(); col++){
    bool empty = true;
    for(int row=0;row < (int)_map.size() && empty; row++){
      if(_map[row][col] == '#')
        empty = false;
    }
    if(empty){
      for(int row=0;row < (int)_map.size(); row++)
        _map[row].insert(_map[row].begin() + col, '.');
      col++;
    }
  }
}

void Universe::setGalaxies(){
  for(int row=0; row < (int)_map.size(); row++){
    for(int col=0; col < (int)_map[0].size(); col++){
      if(_map[row][col] == '#'){
        _galaxies.push_back(Coord{col, row});
      }
    }
  }
}

void Universe::output(){
  for(vector<char> vc: _map){
    for(char c: vc){
      cout << c;
    }
    cout << endl;
  }
}

int Universe::galaxyDistances(){
  int sum = 0;
  for(int a=0; a<(int)_galaxies.size(); a++){
    for(int b=a+1; b<(int)_galaxies.size(); b++){
      sum += _galaxies[a].dist(_galaxies[b]);
    }
  }
  return sum;
}

void Universe::setEmptyLines(){
  for(int row=0; row < (int)_map.size(); row++){
    bool empty = true;
    for(int col=0; col < (int)_map[0].size() && empty; col++){
      if(_map[row][col] == '#')
        empty = false;
    }
    if(empty)
      _emptyRows.push_back(row);
  }
  for(int col=0; col < (int)_map[0].size(); col++){
    bool empty = true;
    for(int row=0;row < (int)_map.size() && empty; row++){
      if(_map[row][col] == '#')
        empty = false;
    }
    if(empty){
      _emptyCols.push_back(col);
    }
  }
}

__int64 Universe::galaxyDistancesWithEmptyLines(){
  __int64 sum = 0;
  for(int a=0; a<(int)_galaxies.size(); a++){
    for(int b=a+1; b<(int)_galaxies.size(); b++){
      __int64 normalDistance = _galaxies[a].dist(_galaxies[b]);
      __int64 extraDistances = 0;
      for(int row: _emptyRows){
        if((_galaxies[a].y() < row && _galaxies[b].y() > row) || (_galaxies[a].y() > row && _galaxies[b].y() < row))
          extraDistances += 999999;
      }
      for(int col: _emptyCols){
        if((_galaxies[a].x() < col && _galaxies[b].x() > col) || (_galaxies[a].x() > col && _galaxies[b].x() < col))
          extraDistances += 999999;
      }
      sum += normalDistance;
      sum += extraDistances;
    }
  }
  return sum;
}
