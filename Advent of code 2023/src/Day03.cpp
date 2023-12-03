#include "Day03.h"

Day03::Day03()
{
  //ctor
}

Day03::~Day03()
{
  //dtor
}

void Day03::part1(string filename){
  InputLoader loader(filename);
  _grid = loader.toVectorChar2d();
  int row = 0;
  int sum = 0;
  while(row < (int)_grid.size()){
    int col = 0;
    while(col < (int)_grid[0].size()){
      int digits = getDigitCount(col, row);
      if(digits>0){
        bool hasSymbolNeithbour = false;
        for(int i=col-1; i<col + digits + 1; i++){
          if(hasSymbolAboveOrBelow(i, row))
            hasSymbolNeithbour = true;
        }
        if(hasSymbolNeithbour)
          sum += getNumber(col, row, digits);
      }
      col += digits;
      col++;
    }
    row++;
  }
  cout << "part 1: " << sum << endl;
}

void Day03::part2(string filename){
  InputLoader loader(filename);
  _grid = loader.toVectorChar2d();
  int sum =0;
  for(int y=0; y<(int)_grid.size(); y++){
    for(int x=0; x<(int)_grid.size(); x++){
      if(_grid[y][x] == '*')
        sum += gearRatio(x, y);
    }
  }
  cout << "part 2: " << sum << endl;
}

GridType Day03::getGridType(int x, int y){
  if(y < 0 || y >= (int)_grid.size() || x < 0 || x >= (int)_grid[0].size())
    return GridType::outOfBounds;
  if(_grid[y][x] == '.')
    return GridType::none;
  if((int)_grid[y][x] >= 48 && (int)_grid[y][x] <= 57)
    return GridType::number;
  return GridType::symbol;
}

int Day03::getDigitCount(int x, int y){
  int digitCount = 0;
  while(getGridType(x, y) == GridType::number){
    x++;
    digitCount++;
  }
  return digitCount;
}

int Day03::getNumber(int x, int y, int digitCount){
  int ret = 0;
  while(digitCount > 0){
    int digit = (int)_grid[y][x] - 48;
    for(int i=0; i<digitCount-1; i++)
      digit *= 10;
    ret += digit;
    x++;
    digitCount--;
  }
  return ret;
}

bool Day03::hasSymbolAboveOrBelow(int x, int y){
  if(getGridType(x, y-1) == GridType::symbol || getGridType(x, y) == GridType::symbol || getGridType(x, y+1) == GridType::symbol)
    return true;
  return false;
}

int Day03::gearRatio(int x, int y){
  int numA;
  int numB;
  int phase = 0;
  for(int testY=y-1; testY<=y+1; testY++){
    bool stillSameNumber = false;
    for(int testX=x-1; testX<=x+1; testX++){
      if(!stillSameNumber && getGridType(testX, testY) == GridType::number){
        if(phase == 0)
          numA = getNumber(testX, testY);
        if(phase == 1)
          numB = getNumber(testX, testY);
        phase++;
      }
      if(getGridType(testX, testY) == GridType::number)
        stillSameNumber = true;
      else
        stillSameNumber = false;
    }
  }
  int ret = numA * numB;
  if(phase != 2)
    ret = 0;
  return ret;
}

int Day03::getNumberStartX(int x, int y){
  while(getGridType(x, y) == GridType::number)
    x--;
  x++;
  return x;
}

int Day03::getNumber(int x, int y){
  x = getNumberStartX(x, y);
  return getNumber(x, y, getDigitCount(x, y));
}
