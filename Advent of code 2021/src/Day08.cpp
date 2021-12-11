#include "Day08.h"

Digit::Digit(const Digit& d){
  for(int i=0; i<7; i++)
    segment[i] = d.segment[i];
  numVal = d.numVal;
}

void Digit::setDigit(string input){
  for(int i=0; i<7; i++)
    segment[i] = false;
  for(char c:input){
    segment[c-97] = true;
    /*cout << segment[c-97] << endl;
    cout << c << endl;
    cout << c-97 << endl;*/
  }
}

void Digit::output(){
  for(int d=0; d<7; d++){
    cout << segment[d] << ", ";
  }
  cout << endl;
}

int Digit::segmentCount(){
  int ans=0;
  for(int i=0; i<7; i++){
    if(segment[i])
      ans++;
  }
  return ans;
}

bool Digit::sharesSegment(Digit d){
  for(int i=0; i<7; i++)
    if(segment[i] && d.segment[i])
      return true;
  return false;
}

Digit Digit::inverse(){
  Digit ret;
  for(int i=0; i<7; i++)
    ret.segment[i] = !segment[i];
  return ret;
}


Day08::Day08()
{
  //ctor
}

Day08::~Day08()
{
  //dtor
}

void Day08::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" "});
  int ans = 0;
  for(vector<string> vs: vvs){
    vs.erase(vs.begin(), vs.begin()+11);
    for(string s: vs)
      if(s.length() == 2 || s.length() == 3 || s.length() == 4 || s.length() == 7)
        ans++;
  }
  cout << "Part 1: " << ans << endl;
}

void Day08::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" ", "|"});
  vector<vector<Digit*>> vvd;
  for(vector<string> vs: vvs){
    vector<Digit*> vd;
    for(string s: vs){
      Digit* d = new Digit();
      d->setDigit(s);
      vd.push_back(d);
    }
    vvd.push_back(vd);
  }
  for(vector<Digit*> vd: vvd){
    Digit* digitRefs[10];
    for(Digit* d: vd){
      if(d->segmentCount()==2){
        d->numVal = 1;
        digitRefs[1] = d;
      }
      if(d->segmentCount()==3){
        d->numVal = 7;
        digitRefs[7] = d;
      }
      if(d->segmentCount()==4){
        d->numVal = 4;
        digitRefs[4] = d;
      }
      if(d->segmentCount()==7){
        d->numVal = 8;
        digitRefs[8] = d;
      }
    }
    for(Digit* d: vd){
      if(d->segmentCount()==6 && d->numVal==-1 && digitRefs[1]->sharesSegment(d->inverse())){
        d->numVal = 6;
        digitRefs[6] = d;
      }
    }
    for(Digit* d: vd){
      if(d->segmentCount()==6 && d->numVal==-1 && digitRefs[4]->inverse().sharesSegment(d->inverse())){
        d->numVal = 9;
        digitRefs[9] = d;
      }
    }
    for(Digit* d: vd){
      if(d->segmentCount()==6 && d->numVal==-1){
        d->numVal = 0;
        digitRefs[0] = d;
      }
    }
    for(Digit* d: vd){
      if(d->segmentCount()==5 && d->numVal==-1 && !digitRefs[4]->inverse().sharesSegment(d->inverse())){
        d->numVal = 2;
        digitRefs[2] = d;
      }
    }
    for(Digit* d: vd){
      if(d->segmentCount()==5 && d->numVal==-1 && digitRefs[1]->sharesSegment(d->inverse())){
        d->numVal = 5;
        digitRefs[5] = d;
      }
    }
    for(Digit* d: vd){
      if(d->segmentCount()==5 && d->numVal==-1){
        d->numVal = 3;
        digitRefs[3] = d;
      }
    }
  }
  int ans=0;
  for(vector<Digit*> vd: vvd){
    int output = 0;
    for(int i=1; i<=4; i++){
      int factor = 1;
      for(int i2=0; i2<i-1; i2++)
        factor = factor * 10;
      output = output + vd[14-i]->numVal*factor;
    }
    ans += output;
  }
  cout << "Part 2: " << ans << endl;
}
