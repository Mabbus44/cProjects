#include "Day04.h"

Day04::Day04()
{
  //ctor
}

Day04::~Day04()
{
  //dtor
}

void Day04::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> input = loader.toVectorStr2d({":", "|"});
  vector<vector<int>> yourNumbers;
  vector<vector<int>> winningNumbers;
  for(vector<string> row: input){
    vector<string> yourNumbersStrings = InputLoader::splitString(row[1], {" "});
    vector<string> winningNumbersStrings = InputLoader::splitString(row[2], {" "});
    vector<int> yourNumbersOne;
    vector<int> winningNumbersOne;
    for(string num: yourNumbersStrings)
      yourNumbersOne.push_back(stoi(num));
    for(string num: winningNumbersStrings)
      winningNumbersOne.push_back(stoi(num));
    yourNumbers.push_back(yourNumbersOne);
    winningNumbers.push_back(winningNumbersOne);
  }
  int totalScore = 0;
  for(int i=0; i<(int)yourNumbers.size(); i++){
    int score = 0;
    for(int num: yourNumbers[i]){
      if(find(winningNumbers[i].begin(), winningNumbers[i].end(), num) != winningNumbers[i].end()){
        if(score == 0)
          score = 1;
        else
          score *= 2;
      }
    }
    totalScore += score;
  }
  cout << "part 1: " << totalScore << endl;
}

void Day04::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> input = loader.toVectorStr2d({":", "|"});
  vector<vector<int>> yourNumbers;
  vector<vector<int>> winningNumbers;
  for(vector<string> row: input){
    vector<string> yourNumbersStrings = InputLoader::splitString(row[1], {" "});
    vector<string> winningNumbersStrings = InputLoader::splitString(row[2], {" "});
    vector<int> yourNumbersOne;
    vector<int> winningNumbersOne;
    for(string num: yourNumbersStrings)
      yourNumbersOne.push_back(stoi(num));
    for(string num: winningNumbersStrings)
      winningNumbersOne.push_back(stoi(num));
    yourNumbers.push_back(yourNumbersOne);
    winningNumbers.push_back(winningNumbersOne);
  }
  vector<int> cardCount(yourNumbers.size(), 1);
  for(int i=0; i<(int)yourNumbers.size(); i++){
    int count = 0;
    for(int num: yourNumbers[i]){
      if(find(winningNumbers[i].begin(), winningNumbers[i].end(), num) != winningNumbers[i].end()){
        count++;
      }
    }
    for(int cardId=i+1; cardId < i + count + 1; cardId++){
      if(cardId < (int)cardCount.size()){
        cardCount[cardId] += cardCount[i];
      }
    }
  }
  int totalCount = 0;
  for(int count: cardCount){
    totalCount += count;
  }
  cout << "part 2: " << totalCount << endl;
}
