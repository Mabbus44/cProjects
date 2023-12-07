#ifndef DAY07_H
#define DAY07_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

enum HandType {highCard=0, onePair=1, twoPair=2, threeOfAKind=3, fullHouse=4, fourOfAKind=5, fiveOfAKind=6};

class Hand{
  public:
    Hand(){}
    Hand(string input){load(input);}
    virtual ~Hand(){}
    bool operator<(const Hand& other);
    bool operator>(const Hand& other);
    void load(string input);
    virtual void setHandType();
    virtual int cardToInt(char card);
    int bid() {return _bid;}
    int handType() {return _handType;}
  protected:
    char _cards[5];
    int _bid;
    HandType _handType;
};

class Hand02: public Hand{
  public:
    Hand02(string input){load(input);}
    virtual void setHandType();
    virtual int cardToInt(char card);
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
