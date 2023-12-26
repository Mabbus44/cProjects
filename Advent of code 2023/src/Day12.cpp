#include "Day12.h"

Day12::Day12()
{
  //ctor
}

Day12::~Day12()
{
  //dtor
}

void Day12::part1(string filename){
  InputLoader loader(filename);
  vector<string> inputs = loader.toVectorStr();
  vector<SpringGroup> springGroups;
  for(string input: inputs)
    springGroups.push_back(SpringGroup(input));
  int sum = 0;
  for(SpringGroup s: springGroups){
    //s.output();
    int var = s.allVariations();
    //cout << "Variations: " << var << endl;
    sum += var;
  }
  cout << "part 1: " << sum << endl;
}

void Day12::part2(string filename){
  InputLoader loader(filename);
  vector<string> inputs = loader.toVectorStr();
  vector<SpringGroup> springGroups;
  for(string input: inputs)
    springGroups.push_back(SpringGroup(input));
  __int64 sum = 0;
  for(SpringGroup s: springGroups){
    s.unfold();
    __int64 var = s.allVariations2();
    //cout << "Variations: " << var << endl;
    sum += var;
  }

  // To high 15040604927357
  cout << "part 2: " << sum << endl;
}

void Combination::output(){
  cout << "  " << pos << ":";
  for(CountPerBunch& cpb: count){
    cpb.output();
  }
  cout << endl;
}

void Group::addCombination(int pos, int bunchCount){
  if(_biggerSibling == nullptr){
    _combinations.push_back(Combination(pos, {CountPerBunch(bunchCount, 1)}));
  }else{
    vector<CountPerBunch> siblingsCombinations = _biggerSibling->combinationsBefore(pos);
    for(CountPerBunch& cPB: siblingsCombinations)
      cPB.bunchCount += bunchCount;
    if(siblingsCombinations.size() > 0)
      _combinations.push_back(Combination(pos, siblingsCombinations));
  }
}

vector<CountPerBunch> Group::combinationsBefore(int pos){
// Pos is the pos of next piece. So pos = next piece, pos-1 = space between, pos-2 = last piece in current group. pos-_groupLen = second piece in current group.
  pos -= _groupLen;
  vector<CountPerBunch> sum;
  for(Combination& c: _combinations){
    if(c.pos < pos){
      for(CountPerBunch& cPBInCombinations: c.count){
        bool addedToSum = false;
        for(CountPerBunch& cPBInSum: sum){
          if(cPBInCombinations.bunchCount == cPBInSum.bunchCount){
            cPBInSum.count += cPBInCombinations.count;
            addedToSum = true;
          }
        }
        if(!addedToSum){
          sum.push_back(cPBInCombinations);
        }
      }
    }else{
      return sum;
    }
  }
  return sum;
}

void Group::output(){
  cout << "Group " << _groupLen << ": " << endl;
  for(Combination& c: _combinations){
    c.output();
  }
  cout << endl;
}

void SpringGroup::load(string input){
  vector<string> springsAndGroups = InputLoader::splitString(input, {" "});
  _springs = vector<char>(springsAndGroups[0].begin(), springsAndGroups[0].end());
  _groups = InputLoader::toInt(InputLoader::splitString(springsAndGroups[1], {","}));
}

bool SpringGroup::fits(int pos, int groupLen){
  if(pos + groupLen > (int)_springs.size())
    return false;
  int lenLeft = groupLen;
  for(int p=pos; p<(int)_springs.size(); p++){
    if(_springs[p] == '.')
      return false;
    if(lenLeft == 1){
      if((p+1 == (int)_springs.size() || _springs[p+1] != '#') &&
         (pos == 0 || _springs[pos-1] != '#'))
        return true;
      return false;
    }
    lenLeft--;
  }
  cout << "Error: Didnt resolve if " << pos << " " << groupLen << " fits" << endl;
  return false;
}

bool SpringGroup::restOk(int pos){
  for(int p=pos; p<(int)_springs.size(); p++)
    if(_springs[p] == '#')
      return false;
  return true;
}

int SpringGroup::variations(int id, int pos, vector<int> history){
  int len = _groups[id];
  history.push_back(pos);
  //cout << "  Variations for _groups[" << id << "], len " << len << ", pos " << pos;
  if(!fits(pos, len)){
    //cout << " does not fit" << endl;
    return 0;
  }
  if(id == (int)_groups.size()-1){
    //cout << " is last";
    if(restOk(pos+len)){
      //cout << " and fits" << endl;
      /*for(int historyPos: history)
        cout << historyPos+1 << ", ";
      cout << endl;*/
      return 1;
    }else{
      //cout << " and does not fit" << endl;
      return 0;
    }
  }
  //cout << " is not last" << endl;
  int sum = 0;
  for(int childPos = pos+len+1; childPos < (int)_springs.size() && (childPos == pos+len+1 || _springs[childPos-1] != '#'); childPos++)
    sum += variations(id+1, childPos, history);
  return sum;
}

int SpringGroup::allVariations(){
  int sum =0;
  for(int p=0; p<(int)_springs.size()-_groups[0]+1 && (p == 0 || _springs[p-1] != '#'); p++){
    //cout << "All variations starting at " << p << endl;
    sum += variations(0, p, {});
  }
  return sum;
}

__int64 SpringGroup::allVariations2(){
  Group* lastGroup = nullptr;
  for(int groupLen: _groups){
    Group* newGroup = new Group(lastGroup, groupLen);
    for(int pos=0; pos < (int)_springs.size(); pos++){
      if(fits(pos, groupLen)){
        newGroup->addCombination(pos, CoveredBunchCount(pos, groupLen));
      }
    }
    _groupObjects.push_back(newGroup);
    lastGroup = newGroup;
    //newGroup->output();
  }
  vector<CountPerBunch> cpbVector = lastGroup->combinationsBefore(_springs.size() + lastGroup->groupLen());
  __int64 sum = 0;
  for(CountPerBunch& cpb: cpbVector){
    if(cpb.bunchCount == _bunchCount)
      sum += cpb.count;
  }
  return sum;
}

int SpringGroup::CoveredBunchCount(int pos, int groupLen){
  int bunchCount = 0;
  bool inBunch = false;
  for(int bunchPos = pos; bunchPos < pos + groupLen; bunchPos++){
    if(_springs[bunchPos] == '#'){
      if(!inBunch){
        bunchCount++;
        inBunch = true;
      }
    }else{
      inBunch = false;
    }
  }
  return bunchCount;
}

void SpringGroup::output(){
  for(char c: _springs)
    cout << c;
  cout << " ";
  for(int i: _groups)
    cout << i << ",";
  cout << endl;
}

void SpringGroup::unfold(){
  vector<char> springCopy = _springs;
  vector<int> groupsCopy = _groups;
  for(int i=0; i<4; i++){
    springCopy.push_back('?');
    springCopy.insert(springCopy.end(), _springs.begin(), _springs.end());
    groupsCopy.insert(groupsCopy.end(), _groups.begin(), _groups.end());
  }
  _springs = springCopy;
  _groups = groupsCopy;
  _bunchCount = 0;
  bool inBunch = false;
  for(char c: _springs){
    if(c == '#'){
      if(!inBunch){
        _bunchCount++;
        inBunch = true;
      }
    }else{
      inBunch = false;
    }
  }
}
