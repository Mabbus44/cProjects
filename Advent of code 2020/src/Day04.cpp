#include "Day04.h"

void Passport::loadData(vector<string> input){
  for(int i=0; i<(int)input.size(); i+=2){
    if(input[i].compare("byr")==0)
      byr=input[i+1];
    if(input[i].compare("iyr")==0)
      iyr=input[i+1];
    if(input[i].compare("eyr")==0)
      eyr=input[i+1];
    if(input[i].compare("hgt")==0)
      hgt=input[i+1];
    if(input[i].compare("hcl")==0)
      hcl=input[i+1];
    if(input[i].compare("ecl")==0)
      ecl=input[i+1];
    if(input[i].compare("pid")==0)
      pid=input[i+1];
    if(input[i].compare("cid")==0)
      cid=input[i+1];
  }
}

bool Passport::hasAllButCid(){
  return(byr.size()>0 &&
     iyr.size()>0 &&
     eyr.size()>0 &&
     hgt.size()>0 &&
     hcl.size()>0 &&
     ecl.size()>0 &&
     pid.size()>0);
}

bool Passport::hasAllButCidStrict(){
  bool output=false;
  if(!hasAllButCid()){
    if(output)
      cout << "basic fail" << endl;
    return false;
  }
  if(stoi(byr)<1920 || stoi(byr)>2002){
    if(output)
      cout << "byr fail: " << byr << endl;
    return false;
  }
  if(stoi(iyr)<2010 || stoi(iyr)>2020){
    if(output)
      cout << "iyr fail: " << iyr << endl;
    return false;
  }
  if(stoi(eyr)<2020 || stoi(eyr)>2030){
    if(output)
      cout << "eyr fail: " << eyr << endl;
    return false;
  }
  if(hgt.substr(hgt.size()-2,2).compare("cm")==0){
    if(stoi(hgt.substr(0,hgt.size()-2))<150 || stoi(hgt.substr(0,hgt.size()-2))>193){
      if(output)
        cout << "hgt cm fail: " << hgt << endl;
      return false;
    }
  }else if(hgt.substr(hgt.size()-2,2).compare("in")==0){
    if(stoi(hgt.substr(0,hgt.size()-2))<59 || stoi(hgt.substr(0,hgt.size()-2))>76){
      if(output)
        cout << "hgt in fail: " << hgt << endl;
      return false;
    }
  }else{
    if(output)
      cout << "hgt fail: " << hgt << endl;
    return false;
  }
  if(hcl[0] != '#' || hcl.size() != 7){
    if(output)
      cout << "hcl start fail: " << hcl << endl;
    return false;
  }
  for(int i=1; i<7; i++){
    if((int)(hcl[i])<48 || ((int)(hcl[i])>57 && (int)(hcl[i])<97) || (int)(hcl[i])>102){
      if(output)
        cout << "hcl fail: " << hcl << endl;
      return false;
    }
  }
  if(!(ecl.compare("amb")==0 ||  ecl.compare("blu")==0 || ecl.compare("brn")==0 || ecl.compare("gry")==0 || ecl.compare("grn")==0 || ecl.compare("hzl")==0 || ecl.compare("oth")==0)){
    if(output)
      cout << "ecl fail: " << ecl << endl;
    return false;
  }
  if(pid.size() != 9){
    if(output)
      cout << "pid len fail: " << pid << endl;
    return false;
  }
  for(int i=0; i<9; i++){
    if((int)(pid[i])<48 || (int)(pid[i])>57){
      if(output)
        cout << "pid fail: " << pid << endl;
      return false;
    }
  }
  return true;
}

void Passport::output(){
  cout << "byr: " << byr << endl;
  cout << "iyr: " << iyr << endl;
  cout << "eyr: " << eyr << endl;
  cout << "hgt: " << hgt << endl;
  cout << "hcl: " << hcl << endl;
  cout << "ecl: " << ecl << endl;
  cout << "pid: " << pid << endl;
  cout << "cid: " << cid << endl;
}

Day04::Day04()
{
  //ctor
}

Day04::~Day04()
{
  //dtor
}

void Day04::part1(string filename){
  InputLoader loader(filename);
  vector<string> vs=loader.toVectorStr();
  vector<Passport*> vp;
  Passport* p = new Passport();
  for(string line:vs){
    if(line.size()>0)
      p->loadData(loader.splitString(line, {":", " "}));
    else{
      vp.push_back(p);
      p=new Passport();
    }
  }
  int count=0;
  for(Passport* p:vp){
    if(p->hasAllButCid())
      count++;
  }
  cout << "part 1: " << count << endl;
}

void Day04::part2(string filename){
  InputLoader loader(filename);
  vector<string> vs=loader.toVectorStr();
  vector<Passport*> vp;
  Passport* p = new Passport();
  for(string line:vs){
    if(line.size()>0)
      p->loadData(loader.splitString(line, {":", " "}));
    else{
      vp.push_back(p);
      p=new Passport();
    }
  }
  int count=0;
  for(Passport* p:vp){
    if(p->hasAllButCidStrict()){
      count++;
    }
  }
  cout << "part 2: " << count << endl;}
