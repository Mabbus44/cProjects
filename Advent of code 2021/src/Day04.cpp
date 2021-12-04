#include "Day04.h"

bool BingoBoard::loadBoard(vector<vector<int>>& input){
  if(input.size()<5){
    cout << "To few rows on loadBoard input";
    return false;
  }
  for(int row=0; row<5; row++){
    if(input[row].size()<5){
      cout << "To few cols on loadBoard input";
      return false;
    }
    board.push_back({});
    for(int col=0; col<5; col++){
      BingoField f;
      f.num = input[row][col];
      board[row].push_back(f);
    }
  }
  return true;
}

void BingoBoard::output(){
  for(vector<BingoField> row : board){
    for(BingoField f : row){
      if(f.crossed)
        cout << "x";
      cout << f.num << "  ";
    }
    cout << endl;
  }
}

bool BingoBoard::hasBingo(){
  bool completeRow = true;
  for(int row=0; row<5; row++){
    for(int col=0; col<5 && completeRow; col++){
      if(!board[row][col].crossed){
        completeRow=false;
      }
    }
    if(completeRow)
      return true;
    completeRow=true;
  }
  for(int col=0; col<5; col++){
    for(int row=0; row<5 && completeRow; row++){
      if(!board[row][col].crossed){
        completeRow=false;
      }
    }
    if(completeRow)
      return true;
    completeRow=true;
  }
  return false;
}

void BingoBoard::drawNumber(vector<int>& drawnNumbers){
  for(int num:drawnNumbers){
    drawnCount++;
    for(int row=0; row<5; row++){
      for(int col=0; col<5; col++){
        if(board[row][col].num == num){
          board[row][col].crossed = true;
          lastNum=num;
          if(hasBingo())
            return;
        }
      }
    }
  }
}

int BingoBoard::getScore(){
  if(score!=-1)
    return score;
  int s=0;
  for(int row=0; row<5; row++){
    for(int col=0; col<5; col++){
      if(!board[row][col].crossed){
        s+=board[row][col].num;
      }
    }
  }
  score = s*lastNum;
  return score;
}

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
  vector<vector<int>> data = loader.toVectorInt2d({",", " "});
  vector<int> drawnNumbers = data[0];
  data.erase(data.begin(), data.begin()+1);
  vector<BingoBoard> boards;
  int bestScore=0;
  int bestDrawnCount=2000000000;
  while(data.size()>=5){
    data.erase(data.begin(), data.begin()+1);
    BingoBoard b;
    boards.push_back(b);
    boards[boards.size()-1].loadBoard(data);
    data.erase(data.begin(), data.begin()+5);
    boards[boards.size()-1].drawNumber(drawnNumbers);
    if(boards[boards.size()-1].drawnCount<bestDrawnCount){
      bestScore = boards[boards.size()-1].getScore();
      bestDrawnCount = boards[boards.size()-1].drawnCount;
    }
  }
  cout << "Part 1: " << bestScore << endl;
}

void Day04::part2(string filename){
  InputLoader loader(filename);
  vector<vector<int>> data = loader.toVectorInt2d({",", " "});
  vector<int> drawnNumbers = data[0];
  data.erase(data.begin(), data.begin()+1);
  vector<BingoBoard> boards;
  int bestScore=0;
  int bestDrawnCount=0;
  while(data.size()>=5){
    data.erase(data.begin(), data.begin()+1);
    BingoBoard b;
    boards.push_back(b);
    boards[boards.size()-1].loadBoard(data);
    data.erase(data.begin(), data.begin()+5);
    boards[boards.size()-1].drawNumber(drawnNumbers);
    if(boards[boards.size()-1].drawnCount>bestDrawnCount){
      bestScore = boards[boards.size()-1].getScore();
      bestDrawnCount = boards[boards.size()-1].drawnCount;
    }
  }
  cout << "Part 2: " << bestScore << endl;
}
