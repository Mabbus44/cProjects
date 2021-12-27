#ifndef DAY02_H
#define DAY02_H
#include <iostream>
#include <vector>
#include "Common.h"

class MyPassword{
  public:
  MyPassword(){}
  MyPassword(vector<string>& vs);
  MyPassword(const MyPassword& p){minLetters=p.minLetters; maxLetters=p.maxLetters; letter=p.letter; pass=p.pass;}
  virtual ~MyPassword(){}
  MyPassword& operator=(const MyPassword& p){minLetters=p.minLetters; maxLetters=p.maxLetters; letter=p.letter; pass=p.pass; return *this;}
  void loadInput(vector<string>& vs);
  bool valid();
  bool valid2();
  int minLetters, maxLetters;
  char letter;
  string pass;
};

class Day02
{
  public:
    Day02();
    virtual ~Day02();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY02_H
