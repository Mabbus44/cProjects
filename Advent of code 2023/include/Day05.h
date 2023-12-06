#ifndef DAY05_H
#define DAY05_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Range{
  public:
    Range(){}
    Range(__int64 s, __int64 l){_start = s; _len = l;}
    virtual ~Range(){}
    __int64 start() {return _start;}
    __int64 len() {return _len;}
    bool tryCombine(Range other);
    void output();
  private:
    __int64 _start;
    __int64 _len;
};

class Conversion{
  public:
    Conversion(){}
    Conversion(string input){load(input);}
    virtual ~Conversion(){}
    void load(string input);
    bool inRange(__int64 input);
    __int64 convert(__int64 input);
    vector<Range> convertRange(vector<Range> input);
    vector<Range> convertRange(Range input);
    void output();
    __int64 start() {return _sourceStart;};
    __int64 end() {return _sourceStart + _length - 1;}
  private:
    __int64 _sourceStart;
    __int64 _destStart;
    __int64 _length;
};

class ConversionCollection{
  public:
    ConversionCollection(){}
    ConversionCollection(vector<string> input){load(input);}
    virtual  ~ConversionCollection(){}
    void load(vector<string> input);
    vector<__int64> convert(vector<string> input);
    __int64 convert(__int64 input);
    vector<Range> convertRange(vector<Range> input);
    vector<Range> rangesOutsideConversions(Range input);
    void output();
  private:
    vector<Conversion> _conversions;
    __int64 _leftBound;
    __int64 _rightBound;
};

class Day05
{
  public:
    Day05();
    virtual ~Day05();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
    vector<Range> combineRanges(vector<Range> input);
};

#endif // DAY05_H
