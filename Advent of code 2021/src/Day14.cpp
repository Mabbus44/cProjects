#include "Day14.h"

Day14::Day14()
{
  for(int i=0; i<26; i++){
    letters[i] = 0;
    for(int i2=0; i2<26; i2++){
      pairs[i*26+i2] = 0;
    }
  }
}

Day14::~Day14()
{
}

void Day14::loadInput(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" -> "});
  state = vvs[0][0];
  startState=state;
  for(int i=0; i<(int)state.length(); i++){
    letters[(int)state[i]-65]++;
    if(i<(int)state.length()-1)
      pairs[((int)state[i]-65)*26+(int)state[i+1]-65]++;
  }
  for(int i=2; i<(int)vvs.size(); i++){
    string inStr = vvs[i][0];
    int inChar0 = (int)inStr[0]-65;
    int inChar1 = (int)inStr[1]-65;
    string outStr = vvs[i][1];
    int outChar = (int)outStr[0]-65;
    vector<int> vi = {inChar0*26+inChar1, inChar0*26+outChar, outChar*26+inChar1, outChar};
    rulesPart2.push_back(vi);
    vector<string> vs = {vvs[i][0], vvs[i][1]};
    rules.push_back(vs);
  }
}

bool Day14::insertAtPosition(int p){
  string subStr = state.substr(p,2);
  for(vector<string> rule:rules){
    if(rule[0] == subStr){
      state.insert(p+1,rule[1]);
      return true;
    }
  }
  return true;
}

void Day14::saveOldState(){
  for(int i=0; i<26; i++){
    oldLetters[i] = letters[i];
    for(int i2=0; i2<26; i2++){
      oldPairs[i*26+i2] = pairs[i*26+i2];
    }
  }
}

void Day14::insertPart2(){
  saveOldState();
  for(vector<int> rule: rulesPart2){
    pairs[rule[0]] -= oldPairs[rule[0]];
    pairs[rule[1]] += oldPairs[rule[0]];
    pairs[rule[2]] += oldPairs[rule[0]];
    letters[rule[3]] += oldPairs[rule[0]];
  }
}

int Day14::countChar(char c){
  int charCount=0;
  for(char c2: state)
    if(c2==c)
      charCount++;
  return charCount;
}

void Day14::part1(string filename){
  loadInput(filename);
  for(int i=0; i<10; i++){
    int position = 0;
    while(position<(int)state.length()-1){
      if(insertAtPosition(position))
        position++;
      position++;
    }
  }
  int leastCount=999999999, mostCount=0;
  for(int ascii=65; ascii<=90; ascii++){
    int charCount = countChar((char)ascii);
    if(charCount>0 && charCount<leastCount)
      leastCount = charCount;
    if(charCount>mostCount)
      mostCount = charCount;
  }
  cout << "Part 1: " << mostCount-leastCount << endl;
}

void Day14::part2(string filename){
  state=startState;
  for(int i=0; i<40; i++)
    insertPart2();
  int64_t leastCount=999999999999999, mostCount=0;
  for(int i=0; i<26; i++){
    if(letters[i]>0 && letters[i]<leastCount)
      leastCount = letters[i];
    if(letters[i]>mostCount)
      mostCount = letters[i];
  }
  cout << "Part 2: " << mostCount-leastCount << endl;
}
