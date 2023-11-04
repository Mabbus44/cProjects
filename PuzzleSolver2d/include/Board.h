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

    Board* closestNeighbour(tuple<double, double> point);
    Board* deepCopy();
    Board* neighbour(int i);
    Piece* pieces(int id);
    Piece* pieces(int x, int y);
    bool inBounds(int x, int y);
    bool matchGoal(Board* goal);
    bool operator==(Board& other);
    int id(){return _id;}
    int pieceCount() {return _pieces.size();}
    int pieceId(Piece* piece);
    int sizeX() {return _sizeX;};
    int sizeY() {return _sizeY;};
    int stepsLeft() {return _stepsLeft;}
    list<string> neighbourDescriptionList();
    string getSaveString();
    tuple<double, double> getMovePoint(Board* other);
    vector<Board*> getNextSteps();
    vector<vector<Piece*>>* boardAddress() {return &_board;}
    void addNeighboursWithoutStepsLeft(list<Board*>* boardList);
    void calculateMovePoints();
    void calculateStepsLeft(int s);
    void clear();
    void connectNeighbours(Board* other);
    void connectNeighbours(vector<Board*>& boards);
    void deletePiece(int id);
    void draw(wxGraphicsContext* gc, bool drawNumbers);
    void free();
    void id(int i){_id = i;}
    void output(string tab = " ", int detailed = 1);
    void stepsLeft(int s) {_stepsLeft = s;}
    void addPiece(Piece* piece);

  protected:

  private:
    int _id;
    int _sizeX;
    int _sizeY;
    int _stepsLeft = -1;
    list<Board*> _neighbours;
    list<int> _neighboursIndex;
    list<tuple<double, double>> _centerPoints;
    vector<vector<Piece*>> _board;
    vector<Piece*> _pieces;
};

#endif // BOARD_H
