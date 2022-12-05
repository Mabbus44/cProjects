#include "Day05.h"

Day05::Day05()
{
  clearStacks();
}

Day05::~Day05()
{
  //dtor
}

void Day05::part1(string filename){
  InputLoader loader(filename);
  vector<vector<int>> moves = loader.toVectorInt2d({"move ", " from ", " to "});
  for(vector<int> move:moves){
    moveCrates(move[0], move[1]-1, move[2]-1);
  }
  string ans="";
  for(list<char> stack: stacks)
    if(stack.size() > 0)
      ans = ans + stack.back();
  cout << "part 1: " << ans << endl;
}

void Day05::part2(string filename){
  clearStacks();
  InputLoader loader(filename);
  vector<vector<int>> moves = loader.toVectorInt2d({"move ", " from ", " to "});
  for(vector<int> move:moves){
    moveCrates2(move[0], move[1]-1, move[2]-1);
  }
  string ans="";
  for(list<char> stack: stacks)
    if(stack.size() > 0)
      ans = ans + stack.back();
  cout << "part 2: " << ans << endl;
}

void Day05::clearStacks(){
  stacks.clear();
  stacks.push_back(string2list("SLW"));
  stacks.push_back(string2list("JTNQ"));
  stacks.push_back(string2list("SCHFJ"));
  stacks.push_back(string2list("TRMWNGB"));
  stacks.push_back(string2list("TRLSDHQB"));
  stacks.push_back(string2list("MJBVFHRL"));
  stacks.push_back(string2list("DWRNJM"));
  stacks.push_back(string2list("BZTFHNDJ"));
  stacks.push_back(string2list("HLQNBFT"));
}

list<char> Day05::string2list(string s){
  list<char> ret;
  for(char c:s){
    ret.push_back(c);
  }
  return ret;
}

void Day05::moveCrates(int count, int from, int to){
  for(int i=0; i<count; i++){
    stacks[to].push_back(stacks[from].back());
    stacks[from].pop_back();
    if(stacks[from].size() == 0)
      return;
  }
}

void Day05::moveCrates2(int count, int from, int to){
  if(count>stacks[from].size())
    count = stacks[from].size();
  list<char>::iterator moveIt = stacks[from].end();
  for(int i=0; i<count; i++)
    moveIt--;
  for(int i=0; i<count; i++){
    stacks[to].push_back(*moveIt);
    moveIt++;
  }
  for(int i=0; i<count; i++)
    stacks[from].pop_back();
}
