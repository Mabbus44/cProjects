#include "Day09.h"

Day09::Day09()
{
  //ctor
}

Day09::~Day09()
{
  //dtor
}

void Day09::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  for(vector<char> vc:vvc){
    vector<int> row;
    for(char c:vc){
      row.push_back((int)c - 48);
    }
    floorMap.push_back(row);
  }
  calculateLowPoints();
  cout << "Part 1: " << calculateRiskLevel() << endl;
}

void Day09::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  for(vector<char> vc:vvc){
    vector<int> row;
    vector<bool> basinRow;
    for(char c:vc){
      row.push_back((int)c - 48);
      basinRow.push_back(false);
    }
    floorMap.push_back(row);
    inBasin.push_back(basinRow);
  }
  vector<int> basinSizes;
  for(int y=0; y<ROWS; y++){
    for(int x=0; x<COLS; x++){
      int basinSize = findBasin(y, x);
      if(basinSize>0)
        basinSizes.push_back(basinSize);
    }
  }
  sort(basinSizes.begin(), basinSizes.end(), greater<int>());
  int ans = basinSizes[0] * basinSizes[1] * basinSizes[2];
  cout << "Part 2: " << ans << endl;
}

void Day09::calculateLowPoints(){
  for(int y=0; y<ROWS; y++){
    for(int x=0; x<COLS; x++){
      if(!((y>0 && floorMap[y-1][x] <= floorMap[y][x]) ||
         (y<ROWS-1 && floorMap[y+1][x] <= floorMap[y][x]) ||
         (x>0 && floorMap[y][x-1] <= floorMap[y][x]) ||
         (x<COLS-1 && floorMap[y][x+1] <= floorMap[y][x]))){
        lowPoints.push_back(floorMap[y][x]);
        //cout << "(" << y << ", " << x << ") " << floorMap[y][x] << endl;
      }
    }
  }
}

int Day09::calculateRiskLevel(){
  int sum=0;
  for(int i:lowPoints)
    sum += (i+1);
  return sum;
}

int Day09::findBasin(int y, int x){
  if(inBasin[y][x] || floorMap[y][x] == 9)
    return 0;
  int basinSize = 1;
  inBasin[y][x] = true;
  if(y>0)
    basinSize += findBasin(y-1, x);
  if(y<ROWS-1)
    basinSize += findBasin(y+1, x);
  if(x>0)
    basinSize += findBasin(y, x-1);
  if(x<COLS-1)
    basinSize += findBasin(y, x+1);
  return basinSize;
}
