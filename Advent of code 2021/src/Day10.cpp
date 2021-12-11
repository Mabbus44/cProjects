#include "Day10.h"

Day10::Day10()
{
  //ctor
}

Day10::~Day10()
{
  //dtor
}

void Day10::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  int sum=0;
  for(vector<char> line: vvc){
    sum += evaluateLine(line);
  }
  cout << "Part 1: " << sum << endl;
}

void Day10::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  vector<int64_t> scores;
  for(vector<char> line: vvc){
    int64_t score = autoComplete(line);
    if(score>0){
      scores.push_back(score);
    }
  }
  sort(scores.begin(), scores.end());
  cout << "Part 2: " << scores[(scores.size()-1)/2] << endl;
}

int Day10::evaluateLine(vector<char>& line){
  vector<char> openers;
  for(char c: line){
    if(c=='(' || c=='[' || c=='{' || c=='<')
      openers.push_back(c);
    if(c==')' || c==']' || c=='}' || c=='>'){
      if(openers.size() == 0)
        return 0; //INCOMPLETE, NO OPENING BRACKET (this does not happend in the input)
      if((openers.back() == '(' && c==')') ||
         (openers.back() == '[' && c==']') ||
         (openers.back() == '{' && c=='}') ||
         (openers.back() == '<' && c=='>'))
        openers.pop_back(); //CLOSE THE BRACKET
      else{
        if(c==')')  //ILLIGAL CLOSING BRACKET
          return 3;
        if(c==']')
          return 57;
        if(c=='}')
          return 1197;
        if(c=='>')
          return 25137;
      }
    }
  }
  return 0;   //NO ERROR, OR NO CLOSING BRACKET
}

int64_t Day10::autoComplete(vector<char>& line){
  vector<char> openers;
  for(char c: line){
    if(c=='(' || c=='[' || c=='{' || c=='<')
      openers.push_back(c);
    if(c==')' || c==']' || c=='}' || c=='>'){
      if(openers.size() == 0)
        return 0; //INCOMPLETE, NO OPENING BRACKET (this does not happend in the input)
      if((openers.back() == '(' && c==')') ||
         (openers.back() == '[' && c==']') ||
         (openers.back() == '{' && c=='}') ||
         (openers.back() == '<' && c=='>'))
        openers.pop_back(); //CLOSE THE BRACKET
      else
        return 0;  //ILLIGAL CLOSING BRACKET
    }
  }
  int64_t points = 0;
  for(int i = openers.size() - 1; i >= 0; i--) {
    if(openers[i]=='(')
      points = points * 5 + 1;
    if(openers[i]=='[')
      points = points * 5 + 2;
    if(openers[i]=='{')
      points = points * 5 + 3;
    if(openers[i]=='<')
      points = points * 5 + 4;
  }
  return points;   //RETURN AUTOCOMPLETE SCORE
}
