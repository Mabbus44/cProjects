#ifndef DAY03_H
#define DAY03_H
#include "Common.h"

enum Mulstep {START, NUM1, SEP, NUM2, END, DONT};
class Day03
{
  public:
    Day03();
    virtual ~Day03();
    void part1(std::string filename);
    void part2(std::string filename);
    bool validStart(std::string& s, int startChar);
    int getNum(std::string& s, int startChar);
    bool validSeparator(std::string& s, int startChar);
    bool validEnd(std::string& s, int startChar);
    int digitCount(int i);
    bool doCommand(std::string& s, int startChar);
    bool dontCommand(std::string& s, int startChar);
  protected:

  private:
};

#endif // DAY03_H
