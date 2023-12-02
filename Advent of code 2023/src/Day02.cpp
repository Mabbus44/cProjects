#include "Day02.h"

void Pick::load(string input){
  vector<string> columns = InputLoader::splitString(input, {","});
  for(string oneColor: columns){
    vector<string> countAndColor = InputLoader::splitString(oneColor, {" "});
    if(countAndColor[1] == RED)
      _red += stoi(countAndColor[0]);
    if(countAndColor[1] == GREEN)
      _green += stoi(countAndColor[0]);
    if(countAndColor[1] == BLUE)
      _blue += stoi(countAndColor[0]);
  }
}

void Pick::output(){
  cout << "  " << _red << " red. " << _green << " green. " << _blue << " blue." << endl;
}

bool Pick::possiblePart1(vector<int> maxVals){
  if(maxVals[0] < _red || maxVals[1] < _green || maxVals[2] < _blue)
    return false;
  return true;
}

void Game::load(string input){
  vector<string> idAndTheRest = InputLoader::splitString(input, {":"});
  string gameId = InputLoader::splitString(idAndTheRest[0], {" "})[1];
  _id = stoi(gameId);

  vector<string> pickInputs = InputLoader::splitString(idAndTheRest[1], {";"});
  _picks.clear();
  for(string pickInput: pickInputs){
    _picks.push_back(Pick(pickInput));
  }
}

void Game::output(){
  cout << "ID: " << _id << endl;
  for(Pick& p: _picks){
    p.output();
  }
}

int Game::possiblePart1(vector<int> maxVals){
  for(Pick& p: _picks)
    if(!p.possiblePart1(maxVals))
      return 0;
  return _id;
}

int Game::power(){
  vector<int> minCubes = {0, 0, 0};
  for(Pick& p: _picks){
    vector<int> pickPower = p.power();
    minCubes[0] = max(minCubes[0], pickPower[0]);
    minCubes[1] = max(minCubes[1], pickPower[1]);
    minCubes[2] = max(minCubes[2], pickPower[2]);
  }
  return minCubes[0] * minCubes[1] * minCubes[2];
}

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
  vector<Game> games;
  vector<string> input = loader.toVectorStr();
  for(string row: input)
    games.push_back(Game(row));
  int sum = 0;
  for(Game& g: games)
    sum += g.possiblePart1({12, 13, 14});
  cout << "part 1: " << sum << endl;
}

void Day02::part2(string filename){
  InputLoader loader(filename);
  vector<Game> games;
  vector<string> input = loader.toVectorStr();
  for(string row: input)
    games.push_back(Game(row));
  int sum = 0;
  for(Game& g: games)
    sum += g.power();
  cout << "part 2: " << sum << endl;
}
