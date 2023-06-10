#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

using namespace std;

enum PIECE_TYPE {ONE_ONE, ONE_TWO, TWO_ONE, TWO_TWO};

class Board;

class Piece
{
  public:
    Piece(){};
    Piece(PIECE_TYPE type, int x, int y){_type = type, _x = x; _y = y;}
    virtual ~Piece(){};
  private:
    PIECE_TYPE _type;
    int _x;
    int _y;
};

class Board
{
  public:
    Board();
    virtual ~Board();
    Board(Board& other){cout << "COPY CONSTRUCTOR" << endl;};
    bool tryAdd(int id, int x, int y);
    void free();
    void getAllPossibleBoards(PIECE_TYPE pieceType, int pieceCount);

  protected:

  private:
    int _squares[4][5];
    Piece* _pieces[10];
};

#endif // BOARD_H
