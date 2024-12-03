#include "Day03.h"

Day03::Day03()
{
  //ctor
}

Day03::~Day03()
{
  //dtor
}

void Day03::part1(std::string filename){
  InputLoader loader(filename);
  std::vector<std::string> input = loader.toVectorStr();
  std::string fullInput = "";
  for(std::string row: input)
    fullInput += ("." + row);
  int pos = 0;
  int step = Mulstep::START;
  int numA, numB, sum = 0;
  while(pos<(int)fullInput.length()){
    if(step == Mulstep::START){
      if(validStart(fullInput, pos)){
        step = Mulstep::NUM1;
        pos += 4;
      }else{
        pos++;
      }
    }else if(step == Mulstep::NUM1){
      int num = getNum(fullInput, pos);
      if(num >= 0){
        numA = num;
        step = Mulstep::SEP;
        pos += digitCount(num);
      }else{
        step = Mulstep::START;
        pos++;
      }
    }else if(step == Mulstep::SEP){
      if(validSeparator(fullInput, pos)){
        step = Mulstep::NUM2;
        pos++;
      }else{
        step = Mulstep::START;
        pos++;
      }
    }else if(step == Mulstep::NUM2){
      int num = getNum(fullInput, pos);
      if(num >= 0){
        numB = num;
        step = Mulstep::END;
        pos += digitCount(num);
      }else{
        step = Mulstep::START;
        pos++;
      }
    }else if(step == Mulstep::END){
      if(validEnd(fullInput, pos)){
        step = Mulstep::START;
        pos++;
        sum += (numA*numB);
      }else{
        step = Mulstep::START;
        pos++;
      }
    }
  }
  std::cout << "part 1: " << sum << std::endl;
}

void Day03::part2(std::string filename){
  InputLoader loader(filename);
  std::vector<std::string> input = loader.toVectorStr();
  std::string fullInput = "";
  for(std::string row: input)
    fullInput += ("." + row);
  int pos = 0;
  int step = Mulstep::START;
  int numA, numB, sum = 0;
  while(pos<(int)fullInput.length()){
    if(dontCommand(fullInput, pos)){
      step = Mulstep::DONT;
      pos += 7;
    }
    if(step == Mulstep::DONT){
      if(doCommand(fullInput, pos)){
        step = Mulstep::START;
        pos += 4;
      }else
        pos++;
    }else if(step == Mulstep::START){
      if(validStart(fullInput, pos)){
        step = Mulstep::NUM1;
        pos += 4;
      }else{
        pos++;
      }
    }else if(step == Mulstep::NUM1){
      int num = getNum(fullInput, pos);
      if(num >= 0){
        numA = num;
        step = Mulstep::SEP;
        pos += digitCount(num);
      }else{
        step = Mulstep::START;
        pos++;
      }
    }else if(step == Mulstep::SEP){
      if(validSeparator(fullInput, pos)){
        step = Mulstep::NUM2;
        pos++;
      }else{
        step = Mulstep::START;
        pos++;
      }
    }else if(step == Mulstep::NUM2){
      int num = getNum(fullInput, pos);
      if(num >= 0){
        numB = num;
        step = Mulstep::END;
        pos += digitCount(num);
      }else{
        step = Mulstep::START;
        pos++;
      }
    }else if(step == Mulstep::END){
      if(validEnd(fullInput, pos)){
        step = Mulstep::START;
        pos++;
        sum += (numA*numB);
      }else{
        step = Mulstep::START;
        pos++;
      }
    }
  }
  std::cout << "part 2: " << sum << std::endl;
}

bool Day03::validStart(std::string& s, int startChar){
  if(s.length()-startChar < 4)
    return false;
  return s.substr(startChar, 4)=="mul(";
}

int Day03::getNum(std::string& s, int startChar){
  std::string num = "";
  bool done = false;
  while(startChar < (int)s.length() && num.length() < 3 && !done){
    char c = s[startChar];
    if((int)c >= 48 && (int)c <= 57)
      num += c;
    else
      done = true;
    startChar++;
  }
  if(num.length() == 0)
    return -1;
  return stoi(num);
}

bool Day03::validSeparator(std::string& s, int startChar){
  if(s.length()-startChar < 1)
    return false;
  return s.substr(startChar, 1)==",";
}

bool Day03::validEnd(std::string& s, int startChar){
  if(s.length()-startChar < 1)
    return false;
  return s.substr(startChar, 1)==")";
}

int Day03::digitCount(int i){
  int mul = 10;
  int digits = 1;
  while(i>=mul){
    mul *= 10;
    digits++;
  }
  return digits;
}

bool Day03::doCommand(std::string& s, int startChar){
  if(s.length()-startChar < 4)
    return false;
  return s.substr(startChar, 4)=="do()";
}

bool Day03::dontCommand(std::string& s, int startChar){
  if(s.length()-startChar < 7)
    return false;
  return s.substr(startChar, 7)=="don't()";
}
