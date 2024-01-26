#include "Day15.h"

void Lens::output(){
  cout << "[" << _label << " " << _focalLen << "]";
}

int InitStep::hash(){
  int hash = 0;
  for(char c: _raw){
    hash += (int)c;
    hash *= 17;
    hash = hash % 256;
  }
  return hash;
}

void InitStep::load(string input){
  _raw = input;
  if(input.find("=") != string::npos){
    vector<string> inputSplit = InputLoader::splitString(input, {"="});
    _label = inputSplit[0];
    _focalLen = InputLoader::toInt({inputSplit[1]})[0];
    _type = StepType::equal;
  }else{
    vector<string> inputSplit = InputLoader::splitString(input, {"-"});
    _label = inputSplit[0];
    _type = StepType::dash;
  }
}

Day15::Day15()
{
  //ctor
}

Day15::~Day15()
{
  //dtor
}

void Day15::part1(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.splitString(loader.toVectorStr()[0], {","});
  vector<InitStep> steps;
  int ans = 0;
  for(string in: input){
    steps.push_back(InitStep(in));
    ans += steps.back().hash();
  }
  cout << "part 1: " << ans << endl;
}

void Day15::part2(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.splitString(loader.toVectorStr()[0], {","});
  vector<InitStep> steps;
  for(string in: input){
    steps.push_back(InitStep(in));
    if(steps.back().type() == StepType::dash)
      dashSign(steps.back());
    else
      equalSign(steps.back());
  }
  cout << "part 2: " << focalPower() << endl;
}

void Day15::equalSign(InitStep& step){
  int boxId=hash(step.label());
  for(int lensId = 0; lensId < (int)_boxes[boxId].size(); lensId++){
    if(_boxes[boxId][lensId].label() == step.label()){
      _boxes[boxId][lensId] = Lens(step.label(), step.focalLen());
      return;
    }
  }
_boxes[boxId].push_back(Lens(step.label(), step.focalLen()));
}

void Day15::dashSign(InitStep& step){
  int boxId=hash(step.label());
  for(int lensId = 0; lensId < (int)_boxes[boxId].size(); lensId++){
    if(_boxes[boxId][lensId].matchLabel(step.label())){
      _boxes[boxId].erase(_boxes[boxId].begin() + lensId);
      return;
    }
  }
}

int Day15::hash(string str){
  int hash = 0;
  for(char c: str){
    hash += (int)c;
    hash *= 17;
    hash = hash % 256;
  }
  return hash;
}

int Day15::focalPower(){
  int power = 0;
  for(int boxId = 0; boxId < 256; boxId++){
    for(int lensId = 0; lensId < (int)_boxes[boxId].size(); lensId++){
      power += ((boxId + 1)*(lensId + 1)*_boxes[boxId][lensId].focalLen());
    }
  }
  return power;
}

void Day15::outputBoxes(){
  for(int boxId = 0; boxId < 256; boxId++){
    if((int)_boxes[boxId].size() > 0){
      cout << "Box " << boxId << ": ";
      for(int lensId=0; lensId < (int)_boxes[boxId].size(); lensId++){
        _boxes[boxId][lensId].output();
      }
      cout << endl;
    }
  }
}
