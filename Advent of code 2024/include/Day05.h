#ifndef DAY05_H
#define DAY05_H
#include "Common.h"

class Day05
{
  public:
    Day05();
    virtual ~Day05();
    void part1(std::string filename);
    void part2(std::string filename);
    bool followsRules(std::vector<int>& update);
    int middleValue(std::vector<int>& update);
    void orderUpdate(std::vector<int>& update);
    std::vector<std::vector<int>> rules;
    std::vector<std::vector<int>> updates;
  protected:

  private:
};

#endif // DAY05_H
