#include "Board.h"

using namespace std;

Board::Board()
{
  for(int y=0; y<5; y++){
    for(int x=0; x<4; x++){
      _squares[x][y] = -1;
    }
  }
  for(int i=0; i<10; i++){
    _pieces[i] = nullptr;
  }
}

Board::~Board()
{
  //dtor
}

void Board::free(){
  for(int i=0; i<10; i++){
    if(_pieces[i] != nullptr){
      delete _pieces[i];
    }
  }
}

bool Board::tryAdd(int id, int x, int y){
  if(id<0 || id>9){
    cout << "Invalid id" << id << endl;
    return false;
  }
  if(_squares[x][y] != -1 || x<0 || y<0)
    return false;
  if(id < 4){
    // Type ONE_ONE
    if(x >= 4 || y >= 5)
      return false;
    _squares[x][y] = id;
    _pieces[id] = new Piece(ONE_ONE, x, y);
  }else if(id < 8){
    // Type ONE_TWO
    if(x >= 4 || y >= 4 || _squares[x][y+1] != -1)
      return false;
    _squares[x][y] = id;
    _squares[x][y+1] = id;
    _pieces[id] = new Piece(ONE_TWO, x, y);
  }else if(id == 8){
    // Type TWO_ONE
    if(x >= 3 || y >= 5 || _squares[x+1][y] != -1)
      return false;
    _squares[x][y] = id;
    _squares[x+1][y] = id;
    _pieces[id] = new Piece(TWO_ONE, x, y);
  }else if(id == 9){
    // Type TWO_TWO
    if(x >= 3 || y >= 4 || _squares[x+1][y+1] != -1 || _squares[x][y+1] != -1 || _squares[x+1][y] != -1)
      return false;
    _squares[x][y] = id;
    _squares[x][y+1] = id;
    _squares[x+1][y] = id;
    _squares[x+1][y+1] = id;
    _pieces[id] = new Piece(TWO_TWO, x, y);
  }
  return true;
}

void Board::getAllPossibleBoards(PIECE_TYPE pieceType, int pieceCount){
  switch(pieceType){
    case ONE_ONE:
      break;
    case ONE_TWO:
      break;
    case TWO_ONE:
      break;
    case TWO_TWO:
      for(int x=0; x<3: x++){
        for(int y=0; y<4; y++){
          Board newBoard(*this);
          if(newBoard.tryAdd(9, x, y)){
            newBoard.getAllPossibleBoard(TWO_ONE, 0);
          }else{
            newBoard.free();
          }
        }
      }
      break;
  }
}
