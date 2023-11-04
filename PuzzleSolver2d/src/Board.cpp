#include "Board.h"
#include <iostream>

Board::Board()
{
  _sizeX = 0;
  _sizeY = 0;
}

Board::Board(int sizeX, int sizeY)
{
  _sizeX = sizeX;
  _sizeY = sizeY;
  vector<Piece*> innerBoardVector(_sizeY, nullptr);
  _board.resize(_sizeX, innerBoardVector);
}

Board::Board(ifstream& file)
{
  if(file.peek() == 'e' || file.peek() == EOF)
    cout << "ERROR: Trying to load board from invalid stream" << endl;
  string line;
  getline(file, line);
  _sizeX = stoi(line);
  getline(file, line);
  _sizeY = stoi(line);
  vector<Piece*> innerBoardVector(_sizeY, nullptr);
  _board.resize(_sizeX, innerBoardVector);

  getline(file, line);
  _id = stoi(line);
  getline(file, line);
  _stepsLeft = stoi(line);
  while(file.peek() != 'e'){
    addPiece(new Piece(file));
  }
  getline(file, line);

  while(file.peek() != 'e'){
    getline(file, line);
    _neighboursIndex.push_back(stoi(line));
  }
  getline(file, line);
}

Board::~Board()
{
  //dtor
}

void Board::addPiece(Piece* piece){
  _pieces.push_back(piece);
  piece->addPieceToBoard(_board);
}

void Board::deletePiece(int id){
  if(id < 0 || id >= (int)_pieces.size())
    return;
  _pieces[id]->removePieceFromBoard(_board);
  _pieces[id]->free();
  delete (_pieces[id]);

  _pieces.erase(_pieces.begin() + id);
}

void Board::output(string tab, int detailed){
  if(detailed == 1){
    cout << tab << "Pieces:" << endl;
    for(Piece* p: _pieces){
      p->output(tab + " ");
    }
    cout << tab << "Board:" << endl;
  }
  for(int y = _sizeY-1; y >= 0; y--){
    cout << tab;
    for(int x = 0; x < _sizeX; x++){
      if(_board[x][y] == nullptr)
        cout << ".";
      else
        cout << _board[x][y]->color();
    }
    cout << endl;
  }
}

Board* Board::deepCopy(){
  Board* newBoard = new Board(_sizeX, _sizeY);
  for(Piece* p: _pieces)
    newBoard->addPiece(p->deepCopy());
  return newBoard;
}

void Board::clear(){
  for(Piece* p: _pieces){
    p->clear();
    delete p;
  }
  _pieces.clear();
  _board.clear();
  _sizeX = 0;
  _sizeY = 0;
}

vector<Board*> Board::getNextSteps(){
  vector<Board*> ret;
  Board* newBoard = this->deepCopy();
  Piece* p;
  for(int pieceId = 0; pieceId < (int)_pieces.size(); pieceId++){
    p = newBoard->_pieces[pieceId];
    p->removePieceFromBoard(newBoard->_board);
    if(p->moveLeft(newBoard->_board)){
      p->addPieceToBoard(newBoard->_board);
      ret.push_back(newBoard);
      newBoard = this->deepCopy();
      p = newBoard->_pieces[pieceId];
      p->removePieceFromBoard(newBoard->_board);
    }
    if(p->moveRight(newBoard->_board, newBoard->_sizeX-2)){
      p->addPieceToBoard(newBoard->_board);
      ret.push_back(newBoard);
      newBoard = this->deepCopy();
      p = newBoard->_pieces[pieceId];
      p->removePieceFromBoard(newBoard->_board);
    }
    if(p->moveDown(newBoard->_board)){
      p->addPieceToBoard(newBoard->_board);
      ret.push_back(newBoard);
      newBoard = this->deepCopy();
      p = newBoard->_pieces[pieceId];
      p->removePieceFromBoard(newBoard->_board);
    }
    if(p->moveUp(newBoard->_board, newBoard->_sizeY-2)){
      p->addPieceToBoard(newBoard->_board);
      ret.push_back(newBoard);
      newBoard = this->deepCopy();
      p = newBoard->_pieces[pieceId];
      p->removePieceFromBoard(newBoard->_board);
    }
    p->addPieceToBoard(newBoard->_board);
  }
  newBoard->clear();
  delete newBoard;
  return ret;
}

bool Board::operator==(Board& other){
  if(this->_sizeX != other._sizeX || this->_sizeY != other._sizeY)
    return false;
  for(int x = 0; x < _sizeX; x++){
    for(int y = 0; y < _sizeY; y++){
      if(_board[x][y] == nullptr){
        if(other._board[x][y] != nullptr)
          return false;
      }else{
        if(other._board[x][y] == nullptr || _board[x][y]->color() != other._board[x][y]->color())
          return false;
      }
    }
  }
  return true;
}

bool Board::matchGoal(Board* goal){
  if(this->_sizeX != goal->_sizeX || this->_sizeY != goal->_sizeY)
    return false;
  for(int x = 0; x < _sizeX; x++){
    for(int y = 0; y < _sizeY; y++){
      if(goal->_board[x][y] != nullptr && (_board[x][y] == nullptr || _board[x][y]->color() != goal->_board[x][y]->color()))
        return false;
    }
  }
  return true;
}

void Board::draw(wxGraphicsContext* gc, bool drawNumbers){
  cout << "Board::draw" << endl;
  for(Piece* piece: _pieces){
    piece->draw(gc, drawNumbers);
  }
  gc->SetPen(wxPen(wxColour("#ffffff")));
  gc->SetBrush(wxBrush(wxColour("#ffffff")));
  wxFont myFont(8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  gc->SetFont(myFont, wxColour("#000000"));
  list<Board*>::iterator neighbourIt = _neighbours.begin();
  for(tuple<double, double> p: _centerPoints){
    gc->DrawRectangle(get<0>(p) * SQUARE_SIZE-11, get<1>(p) * SQUARE_SIZE - 7, 22, 14);
    gc->DrawText(to_string((*neighbourIt)->stepsLeft()), get<0>(p) * SQUARE_SIZE-10, get<1>(p) * SQUARE_SIZE - 6);
    neighbourIt++;
  }
}

void Board::connectNeighbours(Board* other){
  for(Board* n: _neighbours){
    if(other == n)
      return;
  }
  _neighbours.push_back(other);
  other->_neighbours.push_back(this);
}

Piece* Board::pieces(int id){
  if(id < 0 || id >= (int)_pieces.size())
    return nullptr;
  return _pieces[id];
}

Piece* Board::pieces(int x, int y){
  if(x < 0 || x >= (int)_board.size())
    return nullptr;
  if(y < 0 || y >= (int)_board[x].size())
    return nullptr;

  return _board[x][y];
}

bool Board::inBounds(int x, int y){
  if(x < 0 || x >= (int)_board.size())
    return false;
  if(y < 0 || y >= (int)_board[x].size())
    return false;
  return true;
}

int Board::pieceId(Piece* piece){
  int id=0;
  for(Piece* p: _pieces){
    if(p == piece)
      return id;
    id++;
  }
  return -1;
}

void Board::calculateStepsLeft(int s){
  if(_stepsLeft < 0 || _stepsLeft > s)
    _stepsLeft = s;
}

string Board::getSaveString(){
  string ans = "";
  ans.append(to_string(_sizeX) + "\n");
  ans.append(to_string(_sizeY) + "\n");
  ans.append(to_string(_id) + "\n");
  ans.append(to_string(_stepsLeft) + "\n");
  for(Piece* p: _pieces){
    ans.append(p->getSaveString());
  }
  ans.append("e\n");
  for(Board* b: _neighbours){
    ans.append(to_string(b->id()) + "\n");
  }
  ans.append("e\n");
  return ans;
}

void Board::free(){
  for(Piece* p: _pieces){
    p->free();
    delete p;
  }
}

void Board::connectNeighbours(vector<Board*>& boards){
  for(int neighbourId: _neighboursIndex){
    int boardId = 0;
    bool foundNeighbour = false;
    while(boardId < (int)boards.size() && !foundNeighbour){
      if(boards[boardId]->id() == neighbourId){
        foundNeighbour = true;
        _neighbours.push_back(boards[boardId]);
      }
      boardId++;
    }
  }
}

void Board::addNeighboursWithoutStepsLeft(list<Board*>* boardList){
  for(Board* n: _neighbours){
    if(n->stepsLeft() < 0){
      bool alreadyInList = false;
      for(Board* b: *boardList){
        if(b==n){
          alreadyInList = true;
          break;
        }
      }
      if(!alreadyInList)
        boardList->push_back(n);
    }
  }
}

list<string> Board::neighbourDescriptionList(){
  list<string> ans;
  for(Board* n: _neighbours)
    ans.push_back(to_string(n->id()) + ": " + to_string(n->stepsLeft()));
  return ans;
}

Board* Board::neighbour(int i){
  int c = 0;
  for(Board* ans: _neighbours){
    if(c == i)
      return ans;
    c++;
  }
  return nullptr;
}

// Finds the point in the middle of the edge that was moved into a empty field
tuple<double, double> Board::getMovePoint(Board* other){
  // Find squares that are filled and emptied by moving from this board to other board
  list<tuple<double, double>> filledSquares;
  list<tuple<double, double>> emptiedSquares;
  for(double y=0; y<_sizeY; y++){
    for(double x=0; x<_sizeX; x++){
      if(_board[x][y] == nullptr && other->pieces(x, y) != nullptr)
        filledSquares.push_back({x, y});
      if(_board[x][y] != nullptr && other->pieces(x, y) == nullptr)
        emptiedSquares.push_back({x, y});
    }
  }

  // Find center of filled and emptied squares
  tuple<double, double> filledCenter = {0, 0};
  tuple<double, double> emptiedCenter = {0, 0};
  for(tuple<double, double> c: filledSquares){
    get<0>(filledCenter) += get<0>(c);
    get<1>(filledCenter) += get<1>(c);
  }
  get<0>(filledCenter) /= filledSquares.size();
  get<1>(filledCenter) /= filledSquares.size();
  for(tuple<double, double> c: emptiedSquares){
    get<0>(emptiedCenter) += get<0>(c);
    get<1>(emptiedCenter) += get<1>(c);
  }
  get<0>(emptiedCenter) /= (double)emptiedSquares.size();
  get<1>(emptiedCenter) /= (double)emptiedSquares.size();

  // Find direction from filled to emptied squares
  tuple<double, double> dir = {get<0>(emptiedCenter) - get<0>(filledCenter), get<1>(emptiedCenter) - get<1>(filledCenter)};
  // Make length 0.5
  double dirLen = sqrt(get<0>(dir) * get<0>(dir) + get<1>(dir) * get<1>(dir)) * 2.0;
  dir = {get<0>(dir)/dirLen, get<1>(dir)/dirLen};

  return {get<0>(filledCenter) + get<0>(dir) + 0.5, get<1>(filledCenter) + get<1>(dir) + 0.5};
}

void Board::calculateMovePoints(){
  _centerPoints.clear();
  for(Board* n: _neighbours)
    _centerPoints.push_back(getMovePoint(n));

  for(Piece* p: _pieces)
    p->calculateCenter();
}

Board* Board::closestNeighbour(tuple<double, double> point){
  Board* ans = nullptr;
  double ansDist = -1.0;
  list<Board*>::iterator neigbourIt = _neighbours.begin();
  for(tuple<double, double> c: _centerPoints){
    double xDist = get<0>(point) - get<0>(c);
    xDist = xDist * xDist;
    double yDist = get<1>(point) - get<1>(c);
    yDist = yDist * yDist;
    double dist = sqrt(xDist + yDist);
    if(ans == nullptr || dist < ansDist){
      ans = *neigbourIt;
      ansDist = dist;
    }
    neigbourIt++;
  }
  return ans;
}
