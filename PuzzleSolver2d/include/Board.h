#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>
#include "piece.h"
#include <wx/graphics.h>
#include <fstream>
#include <math.h>

using namespace std;

enum Dir {left, right, down,  up};

class Board
{
  public:
    Board();
    Board(int sizeX, int sizeY);
    Board(ifstream& file);
    virtual ~Board();
    void addPiece(Piece* piece);
    void deletePiece(int id);
    void output(string tab = " ", int detailed = 1);
    Board* deepCopy();
    void clear();
    vector<Board*> getNextSteps();
    bool operator==(Board& other);
    bool matchGoal(Board* goal);
    void draw(wxGraphicsContext* gc);
    void connectNeighbours(Board* other);
    int pieceId(Piece* piece);
    void calculateStepsLeft(int s);
    string getSaveString();
    void free();
    void stepsLeft(int s) {_stepsLeft = s;}
    int stepsLeft() {return _stepsLeft;}
    int pieceCount() {return _pieces.size();}
    vector<vector<Piece*>>* boardAddress() {return &_board;}
    Piece* pieces(int id);
    Piece* pieces(int x, int y);
    bool inBounds(int x, int y);
    int sizeX() {return _sizeX;};
    int sizeY() {return _sizeY;};
    int id(){return _id;}
    void id(int i){_id = i;}
    void connectNeighbours(vector<Board*>& boards);
    void addNeighboursWithoutStepsLeft(list<Board*>* boardList);
    list<string> neighbourDescriptionList();
    Board* neighbour(int i);
    tuple<double, double> getMovePoint(Board* other);
    void calculateMovePoints();
    Board* closestNeighbour(tuple<double, double> point);

  protected:

  private:
    vector<Piece*> _pieces;
    vector<vector<Piece*>> _board;
    list<Board*> _neighbours;
    list<int> _neighboursIndex;
    list<tuple<double, double>> _centerPoints;
    int _sizeX;
    int _sizeY;
    int _stepsLeft = -1;
    int _id;
};

#endif // BOARD_H
