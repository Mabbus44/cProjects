#include "Day03.h"
using namespace std;

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
  vector<vector<char>> inputChars = loader.toVectorChar2d();
  vector<vector<int>> inputInts;
  for(int i=0; i<(int)inputChars.size(); i++){
    inputInts.push_back({});
    for(int i2=0; i2<(int)inputChars[i].size();i2++){
      inputInts[i].push_back((int)inputChars[i][i2]-48);
    }
  }
  int multiplier = 1;
  int gamma=0;
  int epsilon=0;
  for(int digitIndex=inputInts[0].size()-1; digitIndex>=0; digitIndex--){
    int ones = 0;
    int zeroes = 0;
    for(vector<int> num:inputInts){
      if(num[digitIndex] == 1)
        ones++;
      else{
        zeroes++;
        if(num[digitIndex] != 0)
          cout << "Error " << num[digitIndex] << " found" << endl;
      }
    }
    if(ones==zeroes)
      cout << "Error: same zero and one count" << endl;
    if(ones>zeroes)
      gamma+=multiplier;
    else
      epsilon+=multiplier;
    multiplier*=2;
  }
  cout << "Part 1: " << gamma*epsilon << endl;
}

void Day03::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> inputChars = loader.toVectorChar2d();
  vector<vector<int>> inputInts;
  for(int i=0; i<(int)inputChars.size(); i++){
    inputInts.push_back({});
    for(int i2=0; i2<(int)inputChars[i].size();i2++){
      inputInts[i].push_back((int)inputChars[i][i2]-48);
    }
  }
  int oxygen=-1;
  int co2=-1;
  vector<vector<int>> inputCopy=inputInts;
  for(int digitIndex=0; digitIndex<(int)inputInts[0].size() && oxygen==-1; digitIndex++){
    int ones = 0;
    int zeroes = 0;
    int commonDigit;
    for(vector<int> num:inputCopy){
      if(num[digitIndex] == 1)
        ones++;
      else
        zeroes++;
    }
    if(ones>=zeroes)
      commonDigit = 1;
    else
      commonDigit = 0;
    for(int i=0; i<inputCopy.size() && oxygen==-1; i++){
      if(inputCopy[i][digitIndex] != commonDigit){
        inputCopy.erase(inputCopy.begin()+i);
        i--;
      }
      if(inputCopy.size() == 1){
        int multiplier = 1;
        oxygen = 0;
        for(int digitIndex2=inputCopy[0].size()-1; digitIndex2>=0; digitIndex2--){
          if(inputCopy[0][digitIndex2] == 1)
            oxygen+=multiplier;
          multiplier*=2;
        }
      }
    }
  }

  inputCopy=inputInts;
  for(int digitIndex=0; digitIndex<(int)inputInts[0].size() && co2==-1; digitIndex++){
    int ones = 0;
    int zeroes = 0;
    int commonDigit;
    for(vector<int> num:inputCopy){
      if(num[digitIndex] == 1)
        ones++;
      else
        zeroes++;
    }
    if(zeroes<=ones)
      commonDigit = 0;
    else
      commonDigit = 1;
    for(int i=0; i<inputCopy.size() && co2==-1; i++){
      if(inputCopy[i][digitIndex] != commonDigit){
        inputCopy.erase(inputCopy.begin()+i);
        i--;
      }
      if(inputCopy.size() == 1){
        int multiplier = 1;
        co2 = 0;
        for(int digitIndex2=inputCopy[0].size()-1; digitIndex2>=0; digitIndex2--){
          if(inputCopy[0][digitIndex2] == 1)
            co2+=multiplier;
          multiplier*=2;
        }
      }
    }
  }

  cout << "Part 2: " << oxygen*co2 << endl;
}
