#include "Day15.h"
#include <map>

Day15::Day15()
{
  //ctor
}

Day15::~Day15()
{
  //dtor
}

void Day15::part1(string filename){
  vector<int> series = {16,11,15,0,1,7};
  int index = 6;

  while(index<2020){
    int last = series[index-1];
    int index2 = index-2;
    while(index2 >= 0 && series[index2] != last)
      index2--;
    if(index2<0)
      series.push_back(0);
    else
      series.push_back(index-1-index2);
    index++;
  }
  cout << "part 1: " << series[2019] << endl;
}

void Day15::part2(string filename){
  map<__int64, __int64> series = {{16, 0},{11, 1},{15, 2},{0, 3},{1, 4}};
  __int64 last = 7;
  __int64 index = 6;
  __int64 next;

  while(index<30000000){
    if(!series.count(last))
      next = 0;
    else
      next = index-1-series[last];
    series[last] = index-1;
    last = next;
    index++;
  }
  cout << "part 2: " << next << endl;
}
