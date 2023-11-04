#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <tuple>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <fstream>

using namespace std;

#define SQUARE_SIZE 50
enum COLOR {maroon, brown, olive, teal, navy, red, orange, yellow, lime, green, cyan, blue, purple, magenta, pink, apricot, beige, mint, lavender, count};
const string COLOR_CODE[COLOR::count] = {"#800000", "#9A6324", "#808000", "#469990", "#000075", "#e6194B", "#f58231", "#ffe119", "#bfef45", "#3cb44b", "#42d4f4", "#4363d8", "#911eb4","#f032e6", "#fabed4", "#ffd8b1", "#fffac8", "#aaffc3", "#dcbeff"};
const string COLOR_NAME[COLOR::count] = {"Maroon", "Brown",  "Olive", "Teal", "Navy", "Red", "Orange", "Yellow", "Lime", "Green", "Cyan", "Blue", "Purple", "Magenta","Pink", "Apricot", "Beige", "Mint", "Lavender"};

class Piece
{
  public:
    Piece();
    Piece(COLOR color) {_color = color;}
    Piece(vector<tuple<int, int>> squares, COLOR color = COLOR::maroon) {_squares = squares; _color = color;}
    Piece(ifstream& file);
    virtual ~Piece();

    COLOR color() {return _color;}
    Piece* deepCopy();
    bool moveDown(vector<vector<Piece*>>& board);
    bool moveLeft(vector<vector<Piece*>>& board);
    bool moveRight(vector<vector<Piece*>>& board, int maxMinusOne);
    bool moveUp(vector<vector<Piece*>>& board, int maxMinusOne);
    int removeSquare(tuple<int, int> square, vector<vector<Piece*>>* board = nullptr);
    int squareCount() {return _squares.size();}
    string getSaveString();
    tuple<int, int> square(int id);
    void addSquare(tuple<int, int> square, vector<vector<Piece*>>* board = nullptr);
    void calculateCenter();
    void clear();
    void color(int c) {_color = static_cast<COLOR>(c);}
    void draw(wxGraphicsContext* gc, bool drawNumber);
    void free();
    void output(string tab = "");
    void removePieceFromBoard(vector<vector<Piece*>>& board);
    void addPieceToBoard(vector<vector<Piece*>>& board);

  protected:

  private:
    COLOR _color = COLOR::maroon;
    tuple<double, double> _centerPoint;
    vector<tuple<int, int>> _squares;
};

#endif // PIECE_H
