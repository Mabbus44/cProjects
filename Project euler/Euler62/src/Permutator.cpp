#include <algorithm>
#include "Permutator.h"

Permutator::Permutator()
{
  fail=false;
  debug = false;
}

void Permutator::populateCubes(__int64 upTo){
  cout << "Populating cubes... ";
  __int64 i=1;
  while(i*i*i<upTo){
    biggestCube = i*i*i;
    cubes.insert(biggestCube);
    i++;
  }
  cout << "done" << endl;
  cout << "Balancing cubes...";
  cubes.balance();
  cout << "done" << endl;
  cout << i-1 << " cubes created below " << upTo << endl;
}

void Permutator::findLowestCube(int permCount){
  __int64 i=0;
  cout << "Finding Smallest number with " << permCount << " permutations... ";
  bool done = false;
  while(!done && !fail){
    i++;
    number=i*i*i;
    separateDigits();
    list<int> digits(this->digits);
    permute(digits);
    if(cubePerms.size() >= permCount)
      done=true;
    else
      cubePerms.clear();
  }
  cout << "done" << endl;
  if(fail)
    cout << "Biggest cube reached, increase the number of cubes and retry" << endl;
  else{
    cout << "Smallest number with " << permCount << " permutations is " << number << " (";
    for(list<__int64>::iterator it=cubePerms.begin(); it!=cubePerms.end(); it++){
      if(it == cubePerms.begin())
        cout << *it;
      else
        cout << ", " << *it;
    }
    cout << ")" << endl;
  }
}

void Permutator::separateDigits(){
  __int64 n = number;
  digits.clear();
  while(n>0){
    digits.push_back(n%10);
    n=n/10;
  }
}

void Permutator::permute(list<int>& digits){
  if(fail)
    return;
  for(int i=0; i<digits.size(); i++){
    list<int> remaningDigits(digits);
    list<int>::iterator it = remaningDigits.begin();
    advance(it, i);
    digitsPerm.push_back(*it);
    remaningDigits.erase(it);
    if(checkCube())
      permute(remaningDigits);
    digitsPerm.pop_back();
  }
}

bool Permutator::checkCube(){
  __int64 minVal = 0;
  __int64 maxVal = 0;
  __int64 power = 1;
  int padding = digits.size() - digitsPerm.size();
  if(*(digitsPerm.begin()) == 0)
    return false;
  for(int i = 0; i<padding; i++){
    maxVal += 9*power;
    power *= 10;
  }
  for(list<int>::reverse_iterator it=digitsPerm.rbegin(); it!=digitsPerm.rend(); it++){
    minVal += *it * power;
    power *= 10;
  }
  maxVal += minVal;
  if(maxVal>biggestCube){
    fail=true;
    return false;
  }
  if(padding > 0)
    return cubes.search(minVal, maxVal);
  else{
    if(cubes.search(maxVal)){
      list<__int64>::iterator it = find(cubePerms.begin(), cubePerms.end(), maxVal);
      if(it == cubePerms.end())
        cubePerms.push_back(maxVal);
    }
    return false;
  }
}
