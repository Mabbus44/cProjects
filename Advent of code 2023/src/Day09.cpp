#include "Day09.h"

Day09::Day09()
{
  //ctor
}

Day09::~Day09()
{
  //dtor
}

void Day09::part1(string filename){
  InputLoader loader(filename);
  vector<string> rows = loader.toVectorStr();
  vector<ValHistory> history;
  __int64 sum = 0;
  for(string row: rows){
    history.push_back(ValHistory(row));
    sum += history.back().getNext();
  }
  cout << "part 1: " << sum << endl;
}

void Day09::part2(string filename){
  InputLoader loader(filename);
  vector<string> rows = loader.toVectorStr();
  vector<ValHistory> history;
  __int64 sum = 0;
  for(string row: rows){
    history.push_back(ValHistory(row));
    sum += history.back().getPrev();
  }
  cout << "part 2: " << sum << endl;
}

ValHistory::ValHistory(vector<__int64> input){
  _history = input;
  setInc();
}

void ValHistory::load(string input){
  _history = InputLoader::toInt64(InputLoader::splitString(input, {" "}));
  setInc();
}

void ValHistory::clear(){
  if(_inc){
    _inc->clear();
    delete _inc;
  }
  _inc = nullptr;
}

__int64 ValHistory::getNext(){
  if(_inc)
    _history.push_back(_history.back() + _inc->getNext());
  else
    _history.push_back(_history.back() + _constInc);
  return _history.back();
}

__int64 ValHistory::getPrev(){
  if(_inc)
    _history.insert(_history.begin(), _history.front() - _inc->getPrev());
  else
    _history.insert(_history.begin(), _history.front() - _constInc);
  return _history.front();
}

void ValHistory::setInc(){
  vector<__int64> delta;
  bool same;
  __int64 sameVal;
  for(int i=1; i<(int)_history.size(); i++){
    __int64 newDelta = _history[i] - _history[i-1];
    if(i == 1){
      same = true;
      sameVal = newDelta;
    }
    delta.push_back(newDelta);
    if(newDelta != sameVal)
      same = false;
  }
  if(same){
    _constInc = sameVal;
  }else{
    _inc = new ValHistory(delta);
  }
}
