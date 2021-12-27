#include "Day06.h"

Day06::Day06()
{
  //ctor
}

Day06::~Day06()
{
  //dtor
}

void Day06::part1(string filename){
  InputLoader loader(filename);
  vector<string> vs=loader.toVectorStr();
  vector<vector<string>> groups;
  vector<string> group;
  for(string s:vs){
    if(s.size()!=0)
      group.push_back(s);
    else{
      groups.push_back(group);
      group.clear();
    }
  }
  int sum=0;
  for(vector<string> g:groups){
    string uniqueChars;
    for(string s:g){
      for(char c:s){
        if(uniqueChars.find(c)==string::npos){
          uniqueChars += c;
        }
      }
    }
    sum += uniqueChars.size();
  }
  cout << "part 1: " << sum << endl;
}

void Day06::part2(string filename){
  InputLoader loader(filename);
  vector<string> vs=loader.toVectorStr();
  vector<vector<string>> groups;
  vector<string> group;
  for(string s:vs){
    if(s.size()!=0)
      group.push_back(s);
    else{
      groups.push_back(group);
      group.clear();
    }
  }
  int sum=0;
  for(vector<string> g:groups){
    string uniqueChars;
    for(int i=0; i<(int)g.size(); i++){
      if(i==0){
        uniqueChars = g[i];
      }else{
        for(int i2=0; i2<(int)uniqueChars.size(); i2++){
          if(g[i].find(uniqueChars[i2])==string::npos){
            uniqueChars.erase(uniqueChars.begin()+i2);
            i2--;
          }
        }
      }
    }
    sum += uniqueChars.size();
  }
  cout << "part 2: " << sum << endl;
}
