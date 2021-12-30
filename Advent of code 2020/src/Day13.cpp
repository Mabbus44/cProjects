#include "Day13.h"

Day13::Day13()
{
  //ctor
}

Day13::~Day13()
{
  //dtor
}

void Day13::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({",", "x"});
  int startTime = stoi(vvs[0][0]);
  vector<int> busses;
  int shortestTimeToNextBus = 999999999;
  int ans;
  for(string s:vvs[1]){
    busses.push_back(stoi(s));
    int timeToNextBus = startTime%busses.back();
    if(timeToNextBus != 0)
      timeToNextBus = busses.back()-timeToNextBus;
    if(timeToNextBus<shortestTimeToNextBus){
      shortestTimeToNextBus = timeToNextBus;
      ans = busses.back()*shortestTimeToNextBus;
    }
  }
  cout << "part 1: " << ans << endl;
}

void Day13::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({","});
  vector<int> busses;
  vector<int> bussGaps;
  vector<int> bussMods;
  int gap=0;
  for(string s:vvs[1]){
    if(s.compare("x") != 0){
      busses.push_back(stoi(s));
      bussGaps.push_back(gap);
      if(gap==0)
        bussMods.push_back(0);
      else
        bussMods.push_back(busses.back()-gap%busses.back());
    }
    gap++;
  }
  int bussId=0;
  int64_t plusNum=busses[bussId];
  int64_t num=plusNum;
  bussId++;
  while(bussId<(int)busses.size()){
    while(num%busses[bussId]!=bussMods[bussId]){
      num += plusNum;
    }
    plusNum*=busses[bussId];
    bussId++;
  }
  cout << "part 2: " << num << endl;
}
