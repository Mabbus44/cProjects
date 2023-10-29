#include "Piece.h"
#include <iostream>

Piece::Piece()
{
}

Piece::~Piece()
{
  //dtor
}

Piece::Piece(ifstream& file)
{
  if(file.peek() == 'e' || file.peek() == EOF)
    cout << "ERROR: Trying to load Piece from invalid stream" << endl;
  string line;
  getline(file, line);
  _color = (COLOR)stoi(line);

  while(file.peek() != 'e'){
    getline(file, line);
    auto pos = line.find(',');
    string strX = line.substr(0, pos);
    string strY = line.substr(pos+1, line.length() - pos);
    _squares.push_back({stoi(strX), stoi(strY)});
  }
  getline(file, line);
}

void Piece::addPieceToBoard(vector<vector<Piece*>>& board){
  for(tuple<int, int> square: _squares){
    board[get<0>(square)][get<1>(square)] = this;
  }
}

void Piece::removePieceFromBoard(vector<vector<Piece*>>& board){
  for(tuple<int, int> square: _squares){
    board[get<0>(square)][get<1>(square)] = nullptr;
  }
}

void Piece::addSquare(tuple<int, int> square, vector<vector<Piece*>>* board){
  _squares.push_back(square);
  if(board == nullptr)
    return;
  (*board)[get<0>(square)][get<1>(square)] = this;
}

int Piece::removeSquare(tuple<int, int> square, vector<vector<Piece*>>* board){
  int squareId = 0;
  for(tuple<int, int> s: _squares){
    if(get<0>(square) == get<0>(s) && get<1>(square) == get<1>(s))
      break;
    squareId++;
  }
  if(squareId == (int)_squares.size())
    return -1;

  _squares.erase(_squares.begin() + squareId);
  if(board == nullptr)
    return squareId;
  (*board)[get<0>(square)][get<1>(square)] = nullptr;
  return squareId;
}

void Piece::output(string tab){
  bool first = true;
  cout << tab << _color << " ";
  for(tuple<int, int> square: _squares){
    if(!first){
      cout << ", ";
    }
    first = false;
    cout << "{" << get<0>(square) << ", " << get<1>(square) << "}";
  }
  cout << endl;
}

Piece* Piece::deepCopy(){
  return new Piece(_squares, _color);
}

void Piece::clear(){
  // No pointers to clear
}

bool Piece::moveLeft(vector<vector<Piece*>>& board){
  for(tuple<int, int>& square: _squares){
    if(get<0>(square) < 1 || board[get<0>(square) - 1][get<1>(square)] != nullptr)
      return false;
  }
  for(tuple<int, int>& square: _squares){
    get<0>(square)--;
  }
  return true;
}

bool Piece::moveRight(vector<vector<Piece*>>& board, int maxMinusOne){
  for(tuple<int, int>& square: _squares){
    if(get<0>(square) > maxMinusOne || board[get<0>(square) + 1][get<1>(square)] != nullptr)
      return false;
  }
  for(tuple<int, int>& square: _squares){
    get<0>(square)++;
  }
  return true;
}

bool Piece::moveDown(vector<vector<Piece*>>& board){
  for(tuple<int, int>& square: _squares){
    if(get<1>(square) < 1 || board[get<0>(square)][get<1>(square) - 1] != nullptr)
      return false;
  }
  for(tuple<int, int>& square: _squares){
    get<1>(square)--;
  }
  return true;
}

bool Piece::moveUp(vector<vector<Piece*>>& board, int maxMinusOne){
  for(tuple<int, int>& square: _squares){
    if(get<1>(square) > maxMinusOne || board[get<0>(square)][get<1>(square) + 1] != nullptr)
      return false;
  }
  for(tuple<int, int>& square: _squares){
    get<1>(square)++;
  }
  return true;
}

void Piece::draw(wxGraphicsContext* gc){
  gc->SetPen(wxPen(wxColour(COLOR_CODE[_color])));
  gc->SetBrush(wxBrush(wxColour(COLOR_CODE[_color])));
  int minX = -1;
  int maxX = -1;
  int minY = -1;
  int maxY = -1;
  for(tuple<int, int>& square: _squares){
    int x = get<0>(square)*SQUARE_SIZE;
    int y = get<1>(square)*SQUARE_SIZE;
    if(minX == -1 || x < minX)
      minX = x;
    if(maxX == -1 || x > maxX)
      maxX = x;
    if(minY == -1 || y < minY)
      minY = y;
    if(maxY == -1 || y > maxY)
      maxY = y;
    gc->DrawRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE);
  }
  if(minX != -1){
    int dx = maxX-minX+SQUARE_SIZE;
    int dy = maxY-minY+SQUARE_SIZE;
    gc->SetPen(wxPen(wxColour("#000000")));
    gc->SetBrush(wxBrush(wxColour("#000000")));
    gc->DrawRectangle(minX, minY, dx, 2);
    gc->DrawRectangle(minX, minY + dy, dx, 2);
    gc->DrawRectangle(minX, minY, 2, dy);
    gc->DrawRectangle(minX + dx, minY, 2, dy);
  }
}

tuple<int, int> Piece::square(int id){
  if(id < 0 || id >= (int)_squares.size())
    return {-1, -1};
  else
    return _squares[id];
}

string Piece::getSaveString(){
  string ans = to_string(_color) + "\n";
  for(tuple<int, int> t: _squares){
    ans.append(to_string(get<0>(t)) + "," + to_string(get<1>(t)) + "\n");
  }
  ans.append("e\n");
  return ans;
}

void Piece::free(){
  // No pointers to free in this class
}
