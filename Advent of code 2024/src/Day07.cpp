#include "Day07.h"

Day07::Day07()
{
  //ctor
}

Day07::~Day07()
{
  //dtor
}

void Day07::part1(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<__int64>> input = loader.toVectorInt642d({":", " "});
  __int64 sum = 0;
  for(std::vector<__int64> row: input){
    if(canSolve(row, 2, row[1]))
      sum += row[0];
  }
  std::cout << "part 1: " << sum << std::endl;
}

void Day07::part2(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<__int64>> input = loader.toVectorInt642d({":", " "});
  __int64 sum = 0;
  for(std::vector<__int64> row: input){
    /*for(__int64 i: row){
      std::cout << i << ", ";
    }
    std::cout << std::endl;*/
    if(canSolve2(row, 2, row[1])){
      sum += row[0];
      //std::cout << "YEP";
    }
    //std::cout << std::endl;
  }
  std::cout << "part 2: " << sum << std::endl;
}

bool Day07::canSolve(std::vector<__int64>& row, int id, __int64 sum){
  if(id >= (int)row.size())
    return sum == row[0];
  if(canSolve(row, id+1, sum*row[id]))
    return true;
  if(canSolve(row, id+1, sum+row[id]))
    return true;
  return false;
}

bool Day07::canSolve2(std::vector<__int64>& row, int id, __int64 sum){
  //std::cout << "canSolve " << id << " " << sum << std::endl;
  if(id >= (int)row.size())
    return sum == row[0];
  if(canSolve2(row, id+1, sum*row[id]))
    return true;
  if(canSolve2(row, id+1, sum+row[id]))
    return true;
  if(canSolve2(row, id+1, concatenate(sum,row[id])))
    return true;
  return false;
}

__int64 Day07::concatenate(__int64 a, __int64 b){
  __int64 bCopy = b/10;
  __int64 ret = a*10;
  while(bCopy != 0){
    bCopy = bCopy/10;
    ret = ret*10;
  }
  return ret+b;
}
