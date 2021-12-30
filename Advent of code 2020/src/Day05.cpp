#include "Day05.h"

Day05::Day05()
{
  //ctor
}

Day05::~Day05()
{
  //dtor
}

void Day05::part1(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  int max=0;
  for(string s:vs){
    int row=getRow(s);
    int seat=getSeat(s);
    if((row*8+seat)>max)
      max=row*8+seat;
  }
  cout << "part 1: " << max << endl;
}

void Day05::part2(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  vector<int> ids;
  for(string s:vs){
    int row=getRow(s);
    int seat=getSeat(s);
    ids.push_back(row*8+seat);
  }
  sort(ids.begin(), ids.end());
  int last = -1;
  int missing = -1;
  for(int i: ids){
    if(last!=-1 && last != i-1)
      missing = i-1;
    last=i;
  }
  cout << "part 2: " << missing << endl;
}

int Day05::getRow(string line){
  int sum=0;
  int mul=1;
  for(int i=6; i>=0; i--){
    if(line[i]=='B')
      sum += mul;
    mul = mul*2;
  }
  return sum;
}

int Day05::getSeat(string line){
  int sum=0;
  int mul=1;
  for(int i=9; i>=7; i--){
    if(line[i]=='R')
      sum += mul;
    mul = mul*2;
  }
  return sum;
}
