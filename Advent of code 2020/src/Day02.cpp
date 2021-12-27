#include "Day02.h"

MyPassword::MyPassword(vector<string>& vs){
  loadInput(vs);
}

void MyPassword::loadInput(vector<string>& vs){
  minLetters = stoi(vs[0]);
  maxLetters = stoi(vs[1]);
  letter = vs[2][0];
  pass = vs[3];
}

bool MyPassword::valid(){
  int count=0;
  for(char c:pass){
    if(c==letter)
      count++;
  }
  return (count>=minLetters && count<=maxLetters);
}

bool MyPassword::valid2(){
  return ((pass[minLetters-1] == letter && pass[maxLetters-1] != letter) ||
          (pass[minLetters-1] != letter && pass[maxLetters-1] == letter));
}

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
  vector<vector<string>> vvs=loader.toVectorStr2d({"-", " ", " "});
  vector<MyPassword> vp;
  for(vector<string> vs:vvs)
    vp.push_back(MyPassword(vs));
  int count=0;
  for(MyPassword p:vp){
    if(p.valid())
      count++;
  }
  cout << "part 1: " << count << endl;
}

void Day02::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs=loader.toVectorStr2d({"-", " ", " "});
  vector<MyPassword> vp;
  for(vector<string> vs:vvs)
    vp.push_back(MyPassword(vs));
  int count=0;
  for(MyPassword p:vp){
    if(p.valid2())
      count++;
  }
  cout << "part 2: " << count << endl;
}
