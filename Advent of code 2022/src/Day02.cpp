#include "Day02.h"

Day02::Day02()
{
  //ctor
}

Day02::~Day02()
{
  //dtor
}

void Day02::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> input = loader.toVectorStr2d({" "});
  vector<vector<Play>> plays = inputToPlay(input);
  int score = 0;
  for(vector<Play> p: plays){
    score += scoreForPlay(p);
  }
  cout << "part 1: " << score << endl;
}

void Day02::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> input = loader.toVectorStr2d({" "});
  vector<vector<Play>> plays = inputToPlay2(input);
  int score = 0;
  for(vector<Play> p: plays){
    score += scoreForPlay(p);
  }
  cout << "part 2: " << score << endl;
}

vector<vector<Play>> Day02::inputToPlay(vector<vector<string>> input)
{
  vector<vector<Play>> ret;
  for(vector<string> vs: input){
    vector<Play> oneMove;
    for(string s: vs){
      if(s == "A" || s == "X")
        oneMove.push_back(ROCK);
      if(s == "B" || s == "Y")
        oneMove.push_back(PAPER);
      if(s == "C" || s == "Z")
        oneMove.push_back(SCISSORS);
    }
    ret.push_back(oneMove);
  }
  return ret;
}

vector<vector<Play>> Day02::inputToPlay2(vector<vector<string>> input)
{
  vector<vector<Play>> ret;
  for(vector<string> vs: input){
    vector<Play> oneMove;
    Play oponentPlay;
    if(vs[0] == "A")
      oponentPlay = ROCK;
    if(vs[0] == "B")
      oponentPlay = PAPER;
    if(vs[0] == "C")
      oponentPlay = SCISSORS;
    oneMove.push_back(oponentPlay);
    if(vs[1] == "X")
      oneMove.push_back(playFromOutcome(oponentPlay, LOSE));
    if(vs[1] == "Y")
      oneMove.push_back(playFromOutcome(oponentPlay, DRAW));
    if(vs[1] == "Z")
      oneMove.push_back(playFromOutcome(oponentPlay, WIN));
    ret.push_back(oneMove);
  }
  return ret;
}

Play Day02::playFromOutcome(Play oponentsPlay, Outcome outcome){
  if(outcome == DRAW)
    return oponentsPlay;
  if(outcome == LOSE){
    if(oponentsPlay == ROCK)
      return SCISSORS;
    if(oponentsPlay == PAPER)
      return ROCK;
    if(oponentsPlay == SCISSORS)
      return PAPER;
  }
  if(oponentsPlay == ROCK)
    return PAPER;
  if(oponentsPlay == PAPER)
    return SCISSORS;
  if(oponentsPlay == SCISSORS)
    return ROCK;
  cout << "MAJOR ERROR";
}

int Day02::scoreForPlay(vector<Play> play){
  int score = 0;
  if(play[0] == play[1])
    score += 3;
  else if((play[0] == ROCK &&     play[1] == PAPER) ||
          (play[0] == PAPER &&    play[1] == SCISSORS) ||
          (play[0] == SCISSORS && play[1] == ROCK))
    score += 6;
  if(play[1] == ROCK)
    score += 1;
  if(play[1] == PAPER)
    score += 2;
  if(play[1] == SCISSORS)
    score += 3;
  return score;
}
