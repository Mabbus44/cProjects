#include "Day03.h"

Day03::Day03()
{
  //ctor
}

Day03::~Day03()
{
  //dtor
}

void Day03::part1(string filename){
  InputLoader loader(filename);
  vector<string> backpacks = loader.toVectorStr();
  int sum = 0;
  for(string backpack: backpacks){
    sum += priority(findDouplicate(backpack));
  }
  cout << "part 1: " << sum << endl;
}

void Day03::part2(string filename){
  InputLoader loader(filename);
  vector<string> backpacks = loader.toVectorStr();
  vector<vector<string>> groups;
  vector<string> group;
  int sum = 0;
  for(string backpack: backpacks){
    group.push_back(backpack);
    if(group.size() == 3){
      sum += priority(findCommon(group));
      groups.push_back(group);
      group.clear();
    }
  }
  cout << "part 2: " << sum << endl;
}

char Day03::findDouplicate(string backpack){
  string firstHalf = backpack.substr(0, backpack.length()/2);
  string secondHalf = backpack.substr(backpack.length()/2, backpack.length()/2);
  for(char c1:firstHalf){
    for(char c2:secondHalf){
      if(c1==c2)
        return c1;
    }
  }
}

int Day03::priority(char c){
  int ret = (int)c;
  if(ret>96)
    ret -= 96;
  else
    ret -= 38;
  return ret;
}

char Day03::findCommon(vector<string> group){
  if(group.size() != 3)
    cout << "ERROR, must be size 3" << endl;
  for(char c1: group[0]){
    for(char c2: group[1])
      if(c1==c2)
        for(char c3: group[2])
          if(c2==c3)
            return c1;
  }
}
