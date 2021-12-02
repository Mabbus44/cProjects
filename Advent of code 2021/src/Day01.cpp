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
  int lastDepth=2000000000;
  int ans = 0;
  InputLoader loader(filename);
  vector<int> depths = loader.toVectorInt();
  for(int i: depths){
    if(lastDepth<i)
      ans++;
    lastDepth=i;
  }
  cout << "part 1: " << ans << endl;
}

void Day01::part2(string filename){
  int lastDepth[3]={200000000,200000000,200000000};
  int sum = 2000000000, lastSum = 2000000000;
  int ans = 0;
  InputLoader loader(filename);
  vector<int> depths = loader.toVectorInt();
  for(int i: depths){
    lastDepth[0] = lastDepth[1];
    lastDepth[1] = lastDepth[2];
    lastDepth[2] = i;
    sum = lastDepth[0]+lastDepth[1]+lastDepth[2];
    if(lastSum<sum)
      ans++;
    lastSum=sum;
  }
  cout << "part 2: " << ans << endl;
}
