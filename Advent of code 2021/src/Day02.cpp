#include "Day02.h"

Day02::Day02()
{
  //ctor
}

Day02::~Day02()
{
  //dtor
}

void Day02::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvd = loader.toVectorStr2d({" "});
  vector<vector<int>> vvi;
  for(vector<string> vd:vvd){
    int i;
    if(vd[0].compare("forward")==0)
      i=FORWARD;
    if(vd[0].compare("up")==0)
      i=UP;
    if(vd[0].compare("down")==0)
      i=DOWN;
    vvi.push_back({i, stoi(vd[1])});
  }
  int h=0;
  int d=0;
  for(vector<int> vi:vvi){
    switch(vi[0]){
    case FORWARD:
      h+=vi[1];
      break;
    case UP:
      d-=vi[1];
      break;
    case DOWN:
      d+=vi[1];
      break;
    }
  }
  cout << "Day 1: " << d*h << endl;
}

void Day02::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvd = loader.toVectorStr2d({" "});
  vector<vector<int>> vvi;
  for(vector<string> vd:vvd){
    int i;
    if(vd[0].compare("forward")==0)
      i=FORWARD;
    if(vd[0].compare("up")==0)
      i=UP;
    if(vd[0].compare("down")==0)
      i=DOWN;
    vvi.push_back({i, stoi(vd[1])});
  }
  int h=0;
  int d=0;
  int aim=0;
  for(vector<int> vi:vvi){
    switch(vi[0]){
    case FORWARD:
      h+=vi[1];
      d+=(vi[1]*aim);
      break;
    case UP:
      aim-=vi[1];
      break;
    case DOWN:
      aim+=vi[1];
      break;
    }
  }
  cout << "Day 2: " << d*h << endl;
}
