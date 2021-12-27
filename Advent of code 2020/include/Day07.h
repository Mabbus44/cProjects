#ifndef DAY07_H
#define DAY07_H
#include <iostream>
#include <vector>
#include "Common.h"

class Bag{
public:
  Bag(){}
  Bag(vector<string>& input){load(input);}
  Bag(const Bag& b){name=b.name;containCount=b.containCount; containName=b.containName;}
  virtual ~Bag(){}
  Bag& operator=(const Bag& b){name=b.name;containCount=b.containCount; containName=b.containName;return *this;}
  void output();
  void load(vector<string>& input);
  bool contains(string name);
  int countBags();
  string name;
  vector<int> containCount;
  vector<string> containName;
  vector<Bag*> containBag;
};

class Day07
{
  public:
    Day07();
    virtual ~Day07();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY07_H
