#ifndef DAY15_H
#define DAY15_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

enum StepType {equal, dash};

class Lens{
public:
  Lens(){}
  Lens(string l, int f) {_label = l; _focalLen = f;}
  bool matchLabel(string l){return _label == l;}
  int focalLen(){return _focalLen;}
  string label(){return _label;}
  void output();

private:
  string _label;
  int _focalLen;
};

class InitStep{
public:
  InitStep(){}
  InitStep(string input) {load(input);}
  void load(string input);
  int hash();
  string label(){return _label;}
  StepType type(){return _type;}
  int focalLen(){return _focalLen;}
  string raw(){return _raw;}

private:
  string _raw;
  string _label;
  StepType _type;
  int _focalLen;
};

class Day15
{
  public:
    Day15();
    virtual ~Day15();
    void part1(string filename);
    void part2(string filename);
    int hash(string str);
  protected:

  private:
    void equalSign(InitStep& step);
    void dashSign(InitStep& step);
    int focalPower();
    void outputBoxes();
    vector<Lens> _boxes[256];
};

#endif // DAY15_H
