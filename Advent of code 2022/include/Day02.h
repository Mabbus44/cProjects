#ifndef DAY02_H
#define DAY02_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

enum Play {ROCK, PAPER, SCISSORS};
enum Outcome {LOSE, DRAW, WIN};

class Day02
{
  public:
    Day02();
    virtual ~Day02();
    void part1(string filename);
    void part2(string filename);
    vector<vector<Play>> inputToPlay(vector<vector<string>> input);
    vector<vector<Play>> inputToPlay2(vector<vector<string>> input);
    Play playFromOutcome(Play oponentsPlay, Outcome outcome);
    int scoreForPlay(vector<Play> play);
  protected:

  private:
};

#endif // DAY02_H
