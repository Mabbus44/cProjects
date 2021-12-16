#ifndef DAY16_H
#define DAY16_H
#include <iostream>
#include <vector>
#include "Common.h"

class Operator{
  public:
    Operator(){}
    virtual ~Operator(){}
    bool parseInput(string& binaryData);
    int64_t binToInt(string str);
    void free();
    void output(string pad);
    int64_t versionSum();
    int64_t val();
    int64_t versionId;
    int64_t typeId;
    int64_t literalValue=0;
    vector<Operator*> children;
};

class Day16
{
  public:
    Day16();
    virtual ~Day16();
    void part1(string filename);
    void part2(string filename);
    void loadFile(string filename);
    string binaryData;
  protected:

  private:
};

#endif // DAY16_H
