#include "Day01.h"

Day01::Day01()
{
  //ctor
}

Day01::~Day01()
{
  //dtor
}

void Day01::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  int sum = 0;
  for(vector<char> row: input){
    int firstNumber, lastNumber;
    bool firstNumberFound = false;
    for(char c: row){
      if((int)c >= 48 && (int)c <= 57){
        int n = (int)c -48;
        if(!firstNumberFound){
          firstNumber = n;
          firstNumberFound = true;
        }
        lastNumber = n;
      }
    }
    if(firstNumberFound){
      sum += firstNumber*10;
      sum += lastNumber;
    }
  }
  cout << "part 1: " << sum << endl;
}

void Day01::part2(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.toVectorStr();
  vector<vector<string>> matches = {
    {"1", "one"},
    {"2", "two"},
    {"3", "three"},
    {"4", "four"},
    {"5", "five"},
    {"6", "six"},
    {"7", "seven"},
    {"8", "eight"},
    {"9", "nine"}};
  int sum = 0;
  for(string row: input){
    int firstMatchIndex = -1;
    int lastMatchIndex = -1;
    int firstMatchVal = 0;
    int lastMatchVal = 0;
    int matchVal = 0;
    for(vector<string> match: matches){
      matchVal++;
      size_t matchPos = row.find(match[0]);
      size_t matchPos2 = row.find(match[1]);
      if(matchPos == string::npos || (matchPos != string::npos && matchPos2 != string::npos && matchPos2 < matchPos))
        matchPos = matchPos2;
      if(matchPos != string::npos){
        if(firstMatchIndex == -1 || (int)matchPos < firstMatchIndex){
          firstMatchIndex = matchPos;
          firstMatchVal = matchVal;
        }
      }
      matchPos = findLast(match[0], row);
      matchPos2 = findLast(match[1], row);
      if(matchPos == string::npos || (matchPos != string::npos && matchPos2 != string::npos && matchPos2 > matchPos))
        matchPos = matchPos2;
      if(matchPos != string::npos){
        if(lastMatchIndex == -1 || (int)matchPos > lastMatchIndex){
          lastMatchIndex = matchPos;
          lastMatchVal = matchVal;
        }
      }
    }
    sum += firstMatchVal*10;
    sum += lastMatchVal;
  }
  cout << "part 2: " << sum << endl;
}

size_t Day01::findLast(string subStr, string str){
  size_t lastPos = string::npos;
  size_t matchPos = str.find(subStr);
  while(matchPos != string::npos){
    lastPos = matchPos;
    matchPos = str.find(subStr, matchPos+1);
  }
  return lastPos;
}
