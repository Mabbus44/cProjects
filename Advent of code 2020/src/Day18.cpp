#include "Day18.h"

void Expression::load(string input){
  type = ADD;
  exps.clear();
  vector<int> startChar = {0};
  int paraDepth=0;
  for(int cIndex=0; cIndex<(int)input.length(); cIndex++){
    if(paraDepth == 0 && (int)(input[cIndex]) >= 48 && (int)(input[cIndex]) <= 57)
      startChar.push_back(cIndex+1);
    if(input[cIndex] == '(')
      paraDepth++;
    if(input[cIndex] == ')'){
      paraDepth--;
      if(paraDepth == 0)
        startChar.push_back(cIndex+1);
    }
  }
  if(startChar.size() == 1){
    cout << "error: invalid expression string '" << input << "'" << endl;
    return;
  }
  if(startChar.size() == 2){
    paraDepth = 0;
    int paraStart;
    for(int cIndex=0; cIndex<(int)input.length(); cIndex++){
      if(paraDepth == 0 && (int)(input[cIndex]) >= 48 && (int)(input[cIndex]) <= 57)
        val = (int)(input[cIndex]) -48;
      if(paraDepth == 0 && input[cIndex] == '*')
        type = MUL;
      if(paraDepth == 0 && input[cIndex] == '(')
        paraStart = cIndex+1;
      if(input[cIndex] == '(')
        paraDepth++;
      if(input[cIndex] == ')'){
        paraDepth--;
        if(paraDepth == 0)
          exps.push_back(Expression(input.substr(paraStart, cIndex-paraStart)));
      }
    }
    return;
  }
  for(int startCharIndex = 0; startCharIndex < (int)startChar.size()-1; startCharIndex++)
    exps.push_back(Expression(input.substr(startChar[startCharIndex], startChar[startCharIndex+1]-startChar[startCharIndex])));
}

__int64 Expression::getVal(){
  if(exps.size() == 0){
    return val;
  }else{
    __int64 ans = 0;
    for(Expression& e: exps){
      if(e.type==ADD)
        ans += e.getVal();
      else
        ans *= e.getVal();
    }
    return ans;
  }
}

Day18::Day18()
{
  //ctor
}

Day18::~Day18()
{
  //dtor
}

void Day18::part1(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  __int64 sum=0;
  for(string s:vs){
    Expression e(s);
    sum += e.getVal();
  }
  cout << "part 1: " << sum << endl;
}

void Day18::part2(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  __int64 sum=0;
  for(string s:vs){
    for(int cIndex=0; cIndex<(int)s.length(); cIndex++){
      if(s[cIndex] == '+'){
        int paraDepth = 0;
        int cIndex2=cIndex;
        bool foundNumber=false;
        while(!foundNumber || paraDepth!=0){
          cIndex2++;
          if((int)(s[cIndex2]) >= 48 && (int)(s[cIndex2]) <= 57)
            foundNumber = true;
          if(s[cIndex2] == '(')
            paraDepth++;
          if(s[cIndex2] == ')')
            paraDepth--;
        }
        s.insert(cIndex2+1, ")");
        paraDepth = 0;
        cIndex2=cIndex;
        foundNumber=false;
        while(!foundNumber || paraDepth!=0){
          cIndex2--;
          if((int)(s[cIndex2]) >= 48 && (int)(s[cIndex2]) <= 57)
            foundNumber = true;
          if(s[cIndex2] == '(')
            paraDepth++;
          if(s[cIndex2] == ')')
            paraDepth--;
        }
        s.insert(cIndex2, "(");
        cIndex++;
      }
    }
    Expression e(s);
    sum += e.getVal();
  }
  cout << "part 2: " << sum << endl;
}
