#ifndef DAY24_H
#define DAY24_H
#include <iostream>
#include <vector>
#include "Common.h"
#include <iomanip>

enum directions {ne,e,se,sw,w,nw};

extern int GLOBALID;

string intDirToChar(int dir);

class Hex{
public:
  Hex(){for(int i=0; i<6; i++) ngbr[i] = nullptr; id=GLOBALID; GLOBALID++;};
  void connectHex(Hex* other, int dir);
  void output();
  bool calcNewIsWhite();
  bool isWhite = true;
  bool newIsWhite;
  int id;
  Hex* ngbr[6];
};

class Day24
{
  public:
    Day24();
    virtual ~Day24();
    void part1(string filename);
    void part2(string filename);
    Hex* spawnHexRow(Hex* spawnHex, Hex*& lastCreated, int spawnDir, int moveDir, int connectDir, Hex* forbiddenHexAddr=nullptr);
    void spawnHexRound(Hex* spawnHex);
    vector<int> strToInst(string s);
    void flipHex(Hex* center, vector<int> inst);
    int countBlack(Hex* center);
    void applyPattern(Hex* center);
  protected:

  private:
};

#endif // DAY02_H
