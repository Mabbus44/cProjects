#include "Day14.h"

Day14::Day14()
{
  //ctor
}

Day14::~Day14()
{
  //dtor
}

void Day14::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  Dish dish(input);
  dish.moveNorth();
  cout << "part 1: " << dish.calcLoad() << endl;
}

void Day14::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  Dish dish(input);
  vector<Dish> oldResults;
  int cycleStart=-1;
  int cycleLen=-1;
  int finalLoad = 0;
  const int runForCycles = 1000000000;
  for(int i=0; i<runForCycles; i++){
    dish.cycle();
    if(cycleStart == -1){
      for(int i2=0; i2<(int)oldResults.size(); i2++){
        if(cycleStart == -1 && dish == oldResults[i2]){
          cycleStart = i2;
          cycleLen = i - i2;
        }
      }
      if(cycleStart != -1){
        int addCycles = (runForCycles-i-1)/cycleLen;
        i += (addCycles * cycleLen);
      }
      oldResults.push_back(dish);
    }
    if(i == runForCycles-1){
      finalLoad = dish.calcLoad();
    }
  }
  cout << "part 2: " << finalLoad << endl;
}

bool Dish::operator==(Dish& other){
  if(_dish.size() != other._dish.size())
    return false;
  if(_dish[0].size() != other._dish[0].size())
    return false;
  for(int y=0; y<(int)_dish.size(); y++)
    for(int x=0; x<(int)other._dish.size(); x++)
      if(_dish[y][x] != other._dish[y][x])
        return false;
  return true;
}

void Dish::load(vector<vector<char>> input){
  _dish = input;
}

void Dish::moveNorth(){
  for(int col = 0; col<(int)_dish[0].size(); col++){
    for(int row=1; row<(int)_dish.size(); row++){
      int fallRow = row;
      while(fallRow > 0 && _dish[fallRow][col] == 'O' && _dish[fallRow-1][col] == '.'){
        _dish[fallRow][col] = '.';
        _dish[fallRow-1][col] = 'O';
        fallRow--;
      }
    }
  }
}

void Dish::moveWest(){
  for(int row=0; row<(int)_dish.size(); row++){
    for(int col = 1; col<(int)_dish[0].size(); col++){
      int fallCol = col;
      while(fallCol > 0 && _dish[row][fallCol] == 'O' && _dish[row][fallCol-1] == '.'){
        _dish[row][fallCol] = '.';
        _dish[row][fallCol-1] = 'O';
        fallCol--;
      }
    }
  }
}

void Dish::moveSouth(){
  for(int col = 0; col<(int)_dish[0].size(); col++){
    for(int row=(int)_dish.size()-2; row>=0; row--){
      int fallRow = row;
      while(fallRow < (int)_dish.size()-1 && _dish[fallRow][col] == 'O' && _dish[fallRow+1][col] == '.'){
        _dish[fallRow][col] = '.';
        _dish[fallRow+1][col] = 'O';
        fallRow++;
      }
    }
  }
}

void Dish::moveEast(){
  for(int row=0; row<(int)_dish.size(); row++){
    for(int col = (int)_dish[0].size()-2; col>=0; col--){
      int fallCol = col;
      while(fallCol < (int)_dish.size()-1 && _dish[row][fallCol] == 'O' && _dish[row][fallCol+1] == '.'){
        _dish[row][fallCol] = '.';
        _dish[row][fallCol+1] = 'O';
        fallCol++;
      }
    }
  }
}

void Dish::output(){
  for(vector<char>& vc: _dish){
    for(char c: vc){
      cout << c;
    }
    cout << endl;
  }
}

int Dish::calcLoad(){
  int load = 0;
  for(int col = 0; col<(int)_dish[0].size(); col++){
    for(int row=0; row<(int)_dish.size(); row++){
      if(_dish[row][col] == 'O'){
        load+=(_dish.size() - row);
      }
    }
  }
  return load;
}

void Dish::cycle(){
  moveNorth();
  moveWest();
  moveSouth();
  moveEast();
}
