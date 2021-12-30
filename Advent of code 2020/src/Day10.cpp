#include "Day10.h"

Day10::Day10()
{
  //ctor
}

Day10::~Day10()
{
  //dtor
}

void Day10::part1(string filename){
  InputLoader loader(filename);
  vector<int> vi=loader.toVectorInt();
  sort(vi.begin(), vi.end());
  vi.insert(vi.begin(), 0);
  vi.push_back(vi.back()+3);
  int threeDiffCount =0;
  int oneDiffCount=0;
  for(int i=0; i+1<(int)vi.size(); i++){
    if(vi[i+1] == vi[i]+3)
      threeDiffCount++;
    if(vi[i+1] == vi[i]+1)
      oneDiffCount++;
    if(vi[i+1] == vi[i])
      cout << "douplicate" << endl;
  }
  cout << "part 1: " << threeDiffCount*oneDiffCount << endl;
}

void Day10::part2(string filename){
  InputLoader loader(filename);
  vector<int> vi=loader.toVectorInt();
  sort(vi.begin(), vi.end());
  vi.insert(vi.begin(), 0);
  vi.push_back(vi.back()+3);
  int64_t combinations[vi.size()];
  combinations[0] = 1;
  for(int i=1; i<(int)vi.size(); i++){
    combinations[i]=0;
    for(int i2=1; i-i2>=0 && vi[i-i2] >= vi[i]-3; i2++){
      if(i-i2>=0)
        combinations[i] += combinations[i-i2];
    }
  }
  cout << "part 2: " << combinations[vi.size()-1] << endl;}
