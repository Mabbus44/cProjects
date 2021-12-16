#include "Day16.h"

int64_t Operator::val(){
  int64_t ret=0;
  switch(typeId){
    case 0:
      for(Operator* c:children){
        ret += c->val();
      }
      break;
    case 1:
      ret = 1;
      for(Operator* c:children){
        ret *= c->val();
      }
      break;
    case 2:
      ret = 999999999;
      for(Operator* c:children){
        int64_t cVal = c->val();
        if(cVal<ret)
          ret = cVal;
      }
      break;
    case 3:
      ret = 0;
      for(Operator* c:children){
        int64_t cVal = c->val();
        if(cVal>ret)
          ret = cVal;
      }
      break;
    case 4:
      ret = literalValue;
      break;
    case 5:
      ret = 0;
      if(children[0]->val()>children[1]->val())
        ret = 1;
      break;
    case 6:
      ret = 0;
      if(children[0]->val()<children[1]->val())
        ret = 1;
      break;
    case 7:
      ret = 0;
      if(children[0]->val()==children[1]->val())
        ret = 1;
      break;
  }
  return ret;
}

int64_t Operator::versionSum(){
  int64_t vSum=versionId;
  for(Operator* c:children)
    vSum+=c->versionSum();
  return vSum;
}

void Operator::output(string pad){
  cout << pad << "v:" << versionId << " t:" << typeId << " l:" << literalValue << endl;
  for(Operator* c:children){
    c->output(pad+" ");
  }
}

int64_t Operator::binToInt(string str){
  int64_t ans=0;
  int64_t mul=1;
  for(int64_t i=str.size()-1; i>=0; i--){
    if(str[i] == '1')
      ans += mul;
    mul *= 2;
  }
  return ans;
}

bool Operator::parseInput(string& binaryData){
  if(binaryData.size()<6){
    binaryData.clear();
    return false;
  }
  versionId = binToInt(binaryData.substr(0,3));
  typeId = binToInt(binaryData.substr(3,3));
  binaryData.erase(binaryData.begin(), binaryData.begin()+6);
  if(typeId==4){
    bool done = false;
    literalValue =0;
    while(!done){
      literalValue *= 16;
      if(binaryData[0] == '0')
        done=true;
      literalValue += binToInt(binaryData.substr(1,4));
      binaryData.erase(binaryData.begin(), binaryData.begin()+5);
    }
  }else{
    int lengthTypeId = binToInt(binaryData.substr(0,1));
    binaryData.erase(binaryData.begin(), binaryData.begin()+1);
    if(lengthTypeId == 0){
      if(binaryData.size()<15){
        binaryData.clear();
        return false;
      }
      int bitCount = binToInt(binaryData.substr(0,15));
      binaryData.erase(binaryData.begin(), binaryData.begin()+15);
      if((int)binaryData.size()<bitCount){
        binaryData.clear();
        return false;
      }
      string childInput=binaryData.substr(0,bitCount);
      binaryData.erase(binaryData.begin(), binaryData.begin()+bitCount);
      while(childInput.size()>0){
        Operator* newO = new Operator();
        if(newO->parseInput(childInput))
          children.push_back(newO);
        else
          delete newO;
      }
    }else{
      if(binaryData.size()<11){
        binaryData.clear();
        return false;
      }
      int childCount = binToInt(binaryData.substr(0,11));
      binaryData.erase(binaryData.begin(), binaryData.begin()+11);
      for(int i=0; i<childCount; i++){
        Operator* newO = new Operator();
        if(newO->parseInput(binaryData))
          children.push_back(newO);
        else{
          cout << "Warning, should have " << childCount << " children, but failed on child " << i << endl;
          delete newO;
        }
      }
    }
  }
  return true;
}

void Operator::free(){
  for(Operator* c:children){
    c->free();
    delete c;
  }
}

Day16::Day16()
{
  //ctor
}

Day16::~Day16()
{
  //dtor
}

void Day16::loadFile(string filename){
  InputLoader loader(filename);
  vector<string> vvs = loader.toVectorStr();
  binaryData="";
  for(char c: vvs[0]){
    switch(c){
    case '0':
      binaryData = binaryData + "0000";
      break;
    case '1':
      binaryData = binaryData + "0001";
      break;
    case '2':
      binaryData = binaryData + "0010";
      break;
    case '3':
      binaryData = binaryData + "0011";
      break;
    case '4':
      binaryData = binaryData + "0100";
      break;
    case '5':
      binaryData = binaryData + "0101";
      break;
    case '6':
      binaryData = binaryData + "0110";
      break;
    case '7':
      binaryData = binaryData + "0111";
      break;
    case '8':
      binaryData = binaryData + "1000";
      break;
    case '9':
      binaryData = binaryData + "1001";
      break;
    case 'A':
      binaryData = binaryData + "1010";
      break;
    case 'B':
      binaryData = binaryData + "1011";
      break;
    case 'C':
      binaryData = binaryData + "1100";
      break;
    case 'D':
      binaryData = binaryData + "1101";
      break;
    case 'E':
      binaryData = binaryData + "1110";
      break;
    case 'F':
      binaryData = binaryData + "1111";
      break;
    }
  }
}

void Day16::part1(string filename){
  loadFile(filename);
  vector<Operator*> ops;
  bool done=false;
  while(!done){
    Operator* newO = new Operator();
    if(!newO->parseInput(binaryData)){
      delete newO;
      done = true;
    }
    else{
      ops.push_back(newO);
    }
  }
  int versionSum=0;
  for(Operator* o:ops){
    o->output("");
    versionSum+=o->versionSum();
  }
  cout << "Part 1: " << versionSum << endl;
  cout << "Part 2: " << ops[0]->val() << endl;
  for(Operator* o:ops)
    o->free();
}

void Day16::part2(string filename){
}
