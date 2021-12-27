#ifndef DAY04_H
#define DAY04_H
#include <iostream>
#include <vector>
#include "Common.h"

class Passport{
public:
  Passport(){}
  virtual ~Passport(){}
  void loadData(vector<string> input);
  bool hasAllButCid();
  bool hasAllButCidStrict();
  void output();
  string byr, iyr, eyr, hgt, hcl, ecl, pid, cid;
};

class Day04
{
  public:
    Day04();
    virtual ~Day04();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY04_H
