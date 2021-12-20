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
  vector<string> vs = loader.toVectorStr();
  vector<int> vi = loader.toInt(vs);
  int64_t ans=0;
  for(int i1:vi){
    for(int i2:vi){
      if(i1+i2==2020)
        ans=i1*i2;
    }
  }
  cout << "part 1: " <<ans<< endl;
}

void Day01::part2(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  vector<int> vi = loader.toInt(vs);
  int64_t ans=0;
  for(int i1:vi){
    for(int i2:vi){
      for(int i3:vi){
      if(i1+i2+i3==2020)
        ans=i1*i2*i3;
      }
    }
  }
  cout << "part 2: " <<ans<< endl;
}
