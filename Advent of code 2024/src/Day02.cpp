#include "Day02.h"

Day02::Day02()
{
  //ctor
}

Day02::~Day02()
{
  //dtor
}

void Day02::part1(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<int>> input = loader.toVectorInt2d({" "});
  int safeCount = 0;
  for(std::vector<int>& report: input){
    if(safe(report))
      safeCount++;
  }
  std::cout << "part 1: " << safeCount << std::endl;
}

void Day02::part2(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<int>> input = loader.toVectorInt2d({" "});
  int safeCount = 0;
  for(std::vector<int>& report: input)
    if(safe2(report, 0) || safe2(report, 1) || safe2(report, 2))
      safeCount++;
  std::cout << "part 2: " << safeCount << std::endl;
}

bool Day02::safe(std::vector<int>& report){
  bool first=true;
  bool second = false;
  int oldI=1;
  int dir=1;
  for(int i: report){
    if(second){
      second = false;
      if(oldI == i)
        return false;
      if(i<oldI)
        dir=-1;
    }
    int diff = (i-oldI)*dir;
    if(first){
      first = false;
      second = true;
    }else
      if(diff<1 || diff>3)
        return false;
    oldI = i;
  }
  return true;
}

bool Day02::safe2(std::vector<int>& report, int variety){
  bool oneMisstake = false;
  int firstI;
  int oldI;
  int dir;
  switch(variety){
    case 0:
      firstI=1;
      dir = report[1]-report[0];
      oldI = 0;
      break;
    case 1:
      firstI=2;
      dir = report[2]-report[0];
      oldI = 0;
      oneMisstake = true;
      break;
    case 2:
      firstI=2;
      dir = report[2]-report[1];
      oldI = 1;
      oneMisstake = true;
      break;
    default:
      std::cout << "Error: Variety=" << variety << std::endl;
  }
  if(dir == 0)
    return false;
  if(dir>0)
    dir=1;
  else
    dir=-1;
  for(int i=firstI; i<(int)report.size(); i++){
    int diff = (report[i]-report[oldI])*dir;
    if(diff<1 || diff>3){
      if(oneMisstake)
        return false;
      oneMisstake = true;
    }else
      oldI = i;
  }
  return true;
}
