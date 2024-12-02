#ifndef DAY02_H
#define DAY02_H
#include "Common.h"

class Day02
{
  public:
    Day02();
    virtual ~Day02();
    void part1(std::string filename);
    void part2(std::string filename);
    bool safe(std::vector<int>& report);
    bool safe2(std::vector<int>& report, int variety=0);

  protected:

  private:
};

#endif // DAY02_H
