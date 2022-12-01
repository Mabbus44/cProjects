#include "Day01.h"

Day01::Day01()
{
  //ctor
}

Day01::~Day01()
{
  //dtor
}

void Day01::part1(string filename){
  InputLoader loader(filename);
  vector<string> depthsStr = loader.toVectorStr();
  vector<vector<int>> elfs;
  vector<int> currentElf;
  for(string s: depthsStr){
    if(s.length() > 0)
      currentElf.push_back(stoi(loader.trim(s)));
    else{
      elfs.push_back(currentElf);
      currentElf.clear();
    }
  }
  int biggestSum = 0;
  for(vector<int> elf: elfs){
    int sum = 0;
    for(int i: elf){
      sum += i;
    }
    if(sum>biggestSum)
      biggestSum = sum;
  }

  cout << "part 1: " << biggestSum << endl;
}

void Day01::part2(string filename){
  InputLoader loader(filename);
  vector<string> depthsStr = loader.toVectorStr();
  vector<vector<int>> elfs;
  vector<int> currentElf;
  for(string s: depthsStr){
    if(s.length() > 0)
      currentElf.push_back(stoi(loader.trim(s)));
    else{
      elfs.push_back(currentElf);
      currentElf.clear();
    }
  }
  int biggestSum[3] = {0,0,0};
  for(vector<int> elf: elfs){
    int sum = 0;
    for(int i: elf){
      sum += i;
    }
    for(int i=0; i<3; i++){
      if(sum > biggestSum[i]){
        for(int i2=2; i2>i; i2--){
          biggestSum[i2] = biggestSum[i2-1];
        }
        biggestSum[i] = sum;
        break;
      }
    }
  }
  int totalSum = 0;
  for(int i=0; i<3; i++)
    totalSum += biggestSum[i];
  cout << "part 2: " << totalSum << endl;
}
