#include "Day13.h"

Day13::Day13()
{
  //ctor
}

Day13::~Day13()
{
  //dtor
}

void Day13::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  vector<Field> fields;
  int sum = 0;
  while(input.size() > 1){
    fields.push_back(Field(input));
    sum += fields.back().score();
  }
  // to low 22486
  cout << "part 1: " << sum << endl;
}

void Day13::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  vector<Field> fields;
  int sum = 0;
  while(input.size() > 1){
    fields.push_back(Field(input));
    sum += fields.back().score2();
  }
  // to low 9197
  cout << "part 2: " << sum << endl;
}

void Field::load(vector<vector<char>>& input){
  while(input.size() > 0 && input[0].size() > 0){
    _field.push_back(input[0]);
    input.erase(input.begin());
  }
  if(input.size() > 0)
    input.erase(input.begin());
}

void Field::findMirror(){
  _score = 0;
  for(int row = 0; row < (int)_field.size()-1; row++){
    bool identical = false;
    if(identicalRows(row, row+1)){
      identical = true;
      for(int dRow = 1; identical && row-dRow >= 0 && row+dRow+1 < (int)_field.size(); dRow++)
        if(!identicalRows(row-dRow, row+1+dRow))
          identical = false;
    }
    if(identical){
      if(_score > 0){
        cout << "Field actually has multiple mirrors row " << row << " score " << _score << endl;
        output();
      }
      _score += (100*(row+1));
    }
  }
  for(int col = 0; col < (int)_field[0].size()-1; col++){
    bool identical = false;
    if(identicalCols(col, col+1)){
      identical = true;
      for(int dCol = 1; identical && col-dCol >= 0 && col+dCol+1 < (int)_field[0].size(); dCol++)
        if(!identicalCols(col-dCol, col+1+dCol))
          identical = false;
    }
    if(identical){
      if(_score > 0){
        cout << "Field actually has multiple mirrors col " << col << " score " << _score << endl;
        output();
      }
      _score += (col+1);
    }
  }
}

void Field::findMirror2(){
  _score2 = 0;
  for(int row = 0; row < (int)_field.size()-1; row++){
    int diffCount = diffCountRows(row, row+1);
    if(diffCount <= 1){
      for(int dRow = 1; diffCount <= 1 && row-dRow >= 0 && row+dRow+1 < (int)_field.size(); dRow++)
        diffCount += diffCountRows(row-dRow, row+1+dRow);
    }
    if(diffCount == 1){
      if(_score2 > 0){
        cout << "Field actually has multiple mirrors row " << row << " score " << _score2 << endl;
        output();
      }
      _score2 += (100*(row+1));
    }
  }
  for(int col = 0; col < (int)_field[0].size()-1; col++){
    int diffCount = diffCountCols(col, col+1);
    if(diffCount <= 1){
      for(int dCol = 1; diffCount <= 1 && col-dCol >= 0 && col+dCol+1 < (int)_field[0].size(); dCol++)
        diffCount += diffCountCols(col-dCol, col+1+dCol);
    }
    if(diffCount == 1){
      if(_score2 > 0){
        cout << "Field actually has multiple mirrors col " << col << " score " << _score2 << endl;
        output();
      }
      _score2 += (col+1);
    }
  }
}

int Field::score(){
  if(_score==-1)
    findMirror();
  return _score;
}

int Field::score2(){
  if(_score2==-1)
    findMirror2();
  return _score2;
}

bool Field::identicalRows(int rowA, int rowB){
  for(int col = 0; col < (int)_field[0].size(); col++)
    if(_field[rowA][col] != _field[rowB][col])
      return false;
  return true;
}

bool Field::identicalCols(int colA, int colB){
  for(int row = 0; row < (int)_field.size(); row++)
    if(_field[row][colA] != _field[row][colB])
      return false;
  return true;
}

int Field::diffCountRows(int rowA, int rowB){
  int diffCount = 0;
  for(int col = 0; col < (int)_field[0].size(); col++)
    if(_field[rowA][col] != _field[rowB][col])
      diffCount++;
  return diffCount;
}

int Field::diffCountCols(int colA, int colB){
  int diffCount = 0;
  for(int row = 0; row < (int)_field.size(); row++)
    if(_field[row][colA] != _field[row][colB])
      diffCount++;
  return diffCount;
}

void Field::output(){
  for(vector<char>& vc: _field){
    for(char c: vc){
      cout << c;
    }
    cout << endl;
  }
}
