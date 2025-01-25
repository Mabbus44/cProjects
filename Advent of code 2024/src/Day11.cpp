#include "Day11.h"

Day11::Day11()
{
  //ctor
}

Day11::~Day11()
{
  //dtor
}

void Day11::part1(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<__int64>> input = loader.toVectorInt642d({" "});
  numbers.clear();
  std::ranges::copy(input[0], std::back_inserter(numbers));
  for(int blink=0; blink<25; blink++){
    for(std::list<__int64>::iterator numIt=numbers.begin(); numIt != numbers.end(); numIt++){
      operate(numIt);
    }
  }
  std::cout << "part 1: " << numbers.size() << std::endl;
}

void Day11::part2(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<__int64>> input = loader.toVectorInt642d({" "});

  _oldState.clear();
  for(__int64 i: input[0]){
    if(_oldState.contains(i)){
      _oldState[i] = _oldState[i] + 1;
    }else{
      _oldState[i] = 1;
    }
  }

  for(int i=0; i<75; i++){
    for(std::pair<__int64, __int64> p: _oldState){
      int digits = digitCount(p.first);
      if(p.first == 0){
        addToNewState(1, p.second);
      }else if(digits%2==0){
        digits = digits/2;
        __int64 power = 1;
        for(int i=0; i<digits; i++){
          power *= 10;
        }
        addToNewState(p.first / power, p.second);
        addToNewState(p.first % power, p.second);
      }else{
        addToNewState(p.first * 2024, p.second);
      }
    }
    _oldState.clear();
    _oldState = _newState;
    _newState = std::map<__int64, __int64>();
  }

  __int64 totCount = 0;
  for(std::pair<__int64, __int64> p: _oldState){
    totCount += p.second;
  }
  std::cout << "part 2: " << totCount << std::endl;
}

void Day11::operate(std::list<__int64>::iterator numIt){
  int digits = digitCount(*numIt);
  if(*numIt == 0){
    *numIt = 1;
  }else if(digits%2==0){
    digits = digits/2;
    __int64 power = 1;
    for(int i=0; i<digits; i++){
      power *= 10;
    }
    numbers.insert(numIt, (*numIt) / power);
    (*numIt) = (*numIt) % power;
  }else{
    (*numIt) *= 2024;
  }
}

int Day11::digitCount(__int64 num){
  int digits = 1;
  while(num>=10){
    digits++;
    num /= 10;
  }
  return digits;
}

void Day11::addToNewState(__int64 num, __int64 count){
  if(_newState.contains(num))
    _newState[num] = _newState[num] + count;
  else
    _newState[num] = count;
}
