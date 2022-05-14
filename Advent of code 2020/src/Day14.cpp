#include "Day14.h"
#include <map>

Mask::Mask(){}

Mask::Mask(string input){
  load(input);
}

void Mask::load(string input){
  _bits.clear();
  for(char& c: input){
    if(c == '0')
      _bits.insert(_bits.begin(), ZERO);
    if(c == '1')
      _bits.insert(_bits.begin(), ONE);
    if(c == 'X')
      _bits.insert(_bits.begin(), UNCHANGED);
  }

}

void Mask::output(){
  vector<int>::iterator i = _bits.end();
  while (i != _bits.begin())
  {
    --i;
    if(*i == ONE)
      cout << "1";
    if(*i == ZERO)
      cout << "0";
    if(*i == UNCHANGED)
      cout << "X";
  }
  cout << endl;
}

BinNum::BinNum(){
}

BinNum::BinNum(__int64 input){
  load(input);
}

void BinNum::load(__int64 input){
  _bits.clear();
  __int64 power = 1;
  while(power < input)
    power *= 2;
  while(power>0){
    if(power <= input){
      _bits.insert(_bits.begin(), 1);
      input -= power;
    }else{
      if(_bits.size()>0)
        _bits.insert(_bits.begin(), 0);
    }
    power /= 2;
  }
  if(_bits.size()==0)
    _bits.insert(_bits.begin(), 0);
}

void BinNum::applyMask(Mask& m){
  const vector<int> maskBits = m.bits();
  for(int i=0; i<(int)maskBits.size(); i++){
    if(i<(int)_bits.size()){
      if(maskBits[i] == ZERO)
        _bits[i] = 0;
      if(maskBits[i] == ONE)
        _bits[i] = 1;
    }else{
      if(maskBits[i] == ONE){
        for(int i2=_bits.size(); i2<i; i2++)
          _bits.push_back(0);
        _bits.push_back(1);
      }
    }
  }
}

vector<__int64> BinNum::applyMask2(Mask& m){
  vector<__int64> ans;
  const vector<int> maskBits = m.bits();
  int floatCount=0;
  for(int i=0; i<(int)maskBits.size(); i++){
    if(i<(int)_bits.size()){
      if(maskBits[i] == ONE)
        _bits[i] = 1;
      if(maskBits[i] == UNCHANGED){
        _bits[i] = FLOATING;
        floatCount++;
      }
    }else{
      if(maskBits[i] == ONE){
        for(int i2=_bits.size(); i2<i; i2++)
          _bits.push_back(0);
        _bits.push_back(1);
      }
      if(maskBits[i] == UNCHANGED){
        for(int i2=_bits.size(); i2<i; i2++)
          _bits.push_back(0);
        _bits.push_back(FLOATING);
        floatCount++;
      }
    }
  }
  if(floatCount==0)
    ans.push_back(toInt());
  else
    getAllAddresses(ans, 0, 0, floatCount);
  return ans;
}

void BinNum::getAllAddresses(vector<__int64>& addresses, int index, int depth, int maxDepth){
  depth++;
  while(_bits[index] != FLOATING)
    index++;
  for(int i=0; i<2; i++){
    _bits[index] = i;
    if(depth == maxDepth){
      addresses.push_back(toInt());
    }
    else
      getAllAddresses(addresses, index, depth, maxDepth);
  }
  _bits[index] = FLOATING;
}

__int64 BinNum::toInt(){
  __int64 multiplier = 1;
  __int64 ans=0;
  for(int i:_bits){
    if(i==1)
      ans += multiplier;
    multiplier *= 2;
  }
  return ans;
}

void BinNum::output(){
  vector<int>::iterator i = _bits.end();
  while (i != _bits.begin())
  {
    --i;
    if(*i == 1)
      cout << "1";
    if(*i == 0)
      cout << "0";
    if(*i == FLOATING)
      cout << "X";
  }
  cout << endl;
}

BinNum BinNum::operator+(BinNum& other){
  BinNum* a;
  BinNum* b;
  BinNum ans;
  int mem=0;
  if(this->len() > other.len()){
    a = this;
    b = &other;
  }else{
    a = &other;
    b = this;
  }
  for(int i=0; i<a->len(); i++){
    int sum = a->_bits[i] + mem;
    if(i<b->len())
      sum += b->_bits[i];
    ans._bits.push_back(sum%2);
    if(sum>1)
      mem = 1;
    else
      mem = 0;
  }
  if(mem>0)
    ans._bits.push_back(1);
  return ans;
}

Day14::Day14()
{
  //ctor
}

Day14::~Day14()
{
  //dtor
}

void Day14::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({"mem[", "]", " = "});
  Mask mask;
  map<__int64, BinNum> binNumbers;
  for(vector<string> vs: vvs){
    if(vs[0].compare(0, 4, "mask") == 0)
      mask.load(vs[1]);
    else{
      BinNum b(loader.toBigInt({vs[1]})[0]);
      b.applyMask(mask);
      binNumbers[loader.toBigInt({vs[0]})[0]] = b;
    }
  }
  BinNum sum;
  for(pair<const __int64, BinNum>& b: binNumbers){
    sum = sum + b.second;
  }
  cout << "part 1: " << sum.toInt() << endl;
}

void Day14::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({"mem[", "]", " = "});
  Mask mask;
  map<__int64, BinNum> binNumbers;
  for(vector<string> vs: vvs){
    if(vs[0].compare(0, 4, "mask") == 0){
      mask.load(vs[1]);
    }
    else{
      BinNum b(loader.toBigInt({vs[1]})[0]);
      BinNum a(loader.toBigInt({vs[0]})[0]);
      vector<__int64> addresses = a.applyMask2(mask);
      for(__int64 ia:addresses){
        binNumbers[ia] = b;
      }
    }
  }
  BinNum sum;
  for(pair<const __int64, BinNum>& b: binNumbers){
    sum = sum + b.second;
  }
  cout << "part 2: " << sum.toInt() << endl;
}
