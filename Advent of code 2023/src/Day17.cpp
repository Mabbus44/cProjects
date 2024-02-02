#include "Day17.h"

namespace day17{
  Cell::Cell(){
    for(int i=0; i<4; i++){
      _neighbours[i] = nullptr;
      for(int i2=0; i2<10; i2++)
        _bestArrival[i][i2] = -1;
    }
    _finalCell = false;
  }

  void Cell::output(string tab){
    cout << tab << "addr: " << this << endl;
    cout << tab << "(" << _x << ", " << _y << ")" << endl;
    cout << tab << "best: " << *_bestFinnish << endl;
  }

  void Cell::connectNeighbours(Cell* newNeighbour, Dir neighbourDir){
    _neighbours[neighbourDir] = newNeighbour;
    newNeighbour->_neighbours[opositeDir(neighbourDir)] = this;
  }

  void Cell::evaluateCart(Dir incomingDir, int heatLoss, int travelDist, bool dontAddHeatloss){
    if(!dontAddHeatloss)
      heatLoss += _heatLoss;
    //Already have better route
    if((_bestArrival[incomingDir][travelDist] != -1 && _bestArrival[incomingDir][travelDist] <= heatLoss) ||
       (*_bestFinnish != -1 && heatLoss >= *_bestFinnish))
      return;

    if(_finalCell){
      *_bestFinnish = heatLoss;
    }
    for(int i=travelDist; i<3; i++){
      _bestArrival[incomingDir][travelDist] = heatLoss;
    }

    Dir opDir = opositeDir(incomingDir);

    if(opDir != Dir::right && _neighbours[Dir::right] != nullptr && !(incomingDir == Dir::right && travelDist >= 2))
      _neighbours[Dir::right]->evaluateCart(Dir::right, heatLoss, calcTravelDist(incomingDir, Dir::right, travelDist, dontAddHeatloss));
    if(opDir != Dir::down && _neighbours[Dir::down] != nullptr && !(incomingDir == Dir::down && travelDist >= 2))
      _neighbours[Dir::down]->evaluateCart(Dir::down, heatLoss, calcTravelDist(incomingDir, Dir::down, travelDist, dontAddHeatloss));
    if(opDir != Dir::up && _neighbours[Dir::up] != nullptr && !(incomingDir == Dir::up && travelDist >= 2))
      _neighbours[Dir::up]->evaluateCart(Dir::up, heatLoss, calcTravelDist(incomingDir, Dir::up, travelDist, dontAddHeatloss));
    if(opDir != Dir::left && _neighbours[Dir::left] != nullptr && !(incomingDir == Dir::left && travelDist >= 2))
      _neighbours[Dir::left]->evaluateCart(Dir::left, heatLoss, calcTravelDist(incomingDir, Dir::left, travelDist, dontAddHeatloss));
  }

  void Cell::evaluateCart2(Dir incomingDir, int heatLoss, int travelDist, bool dontAddHeatloss){
    if(!dontAddHeatloss)
      heatLoss += _heatLoss;
    //Already have better route
    if((_bestArrival[incomingDir][travelDist] != -1 && _bestArrival[incomingDir][travelDist] <= heatLoss) ||
       (*_bestFinnish != -1 && heatLoss >= *_bestFinnish))
      return;

    if(_finalCell && travelDist >= 3){
      *_bestFinnish = heatLoss;
    }
    for(int i=travelDist; i<10; i++){
      _bestArrival[incomingDir][travelDist] = heatLoss;
    }

    Dir opDir = opositeDir(incomingDir);

    if(opDir != Dir::right && _neighbours[Dir::right] != nullptr && !(incomingDir == Dir::right && travelDist >= 9) && !(incomingDir != Dir::right && travelDist < 3))
      _neighbours[Dir::right]->evaluateCart2(Dir::right, heatLoss, calcTravelDist(incomingDir, Dir::right, travelDist, dontAddHeatloss));
    if(opDir != Dir::down && _neighbours[Dir::down] != nullptr && !(incomingDir == Dir::down && travelDist >= 9) && !(incomingDir != Dir::down && travelDist < 3))
      _neighbours[Dir::down]->evaluateCart2(Dir::down, heatLoss, calcTravelDist(incomingDir, Dir::down, travelDist, dontAddHeatloss));
    if(opDir != Dir::up && _neighbours[Dir::up] != nullptr && !(incomingDir == Dir::up && travelDist >= 9) && !(incomingDir != Dir::up && travelDist < 3))
      _neighbours[Dir::up]->evaluateCart2(Dir::up, heatLoss, calcTravelDist(incomingDir, Dir::up, travelDist, dontAddHeatloss));
    if(opDir != Dir::left && _neighbours[Dir::left] != nullptr && !(incomingDir == Dir::left && travelDist >= 9) && !(incomingDir != Dir::left && travelDist < 3))
      _neighbours[Dir::left]->evaluateCart2(Dir::left, heatLoss, calcTravelDist(incomingDir, Dir::left, travelDist, dontAddHeatloss));
  }

  int Cell::calcTravelDist(Dir incomingDir, Dir outgoingDir, int travelDist, bool noIncomingDir){
    if(!noIncomingDir && incomingDir == outgoingDir)
      return ++travelDist;
    return 0;
  }

  Dir Cell::opositeDir(Dir dir){
    if(dir == Dir::left)
      return Dir::right;
    if(dir == Dir::right)
      return Dir::left;
    if(dir == Dir::up)
      return Dir::down;
    if(dir == Dir::down)
      return Dir::up;
    cout << "ERROR: Invalid dir in OpositeDir" << endl;
    return Dir::left;
  }

  Day17::Day17()
  {
    //ctor
  }

  Day17::~Day17()
  {
    //dtor
  }

  void Day17::part1(string filename){
    InputLoader loader(filename);
    vector<vector<char>> input = loader.toVectorChar2d();
    vector<vector<Cell*>> cells;
    int* bestVal = new int;
    (*bestVal) = -1;
    for(int y=0; y<(int)input.size(); y++){
      cells.push_back(vector<Cell*>());
      for(int x=0; x<(int)input[0].size(); x++){
        cells.back().push_back(new Cell((int)(input[y][x])-48, x, y, bestVal));
        if(y>0)
          cells[y][x]->connectNeighbours(cells[y-1][x], Dir::up);
        if(x>0)
          cells[y][x]->connectNeighbours(cells[y][x-1], Dir::left);
      }
    }
    cells.back().back()->finalCell(true);
    cells.front().front()->evaluateCart(Dir::right, 0, 0, true);
    cout << "part 1: " << *bestVal << endl;
  }

  void Day17::part2(string filename){
    InputLoader loader(filename);
    vector<vector<char>> input = loader.toVectorChar2d();
    vector<vector<Cell*>> cells;
    int* bestVal = new int;
    (*bestVal) = -1;
    for(int y=0; y<(int)input.size(); y++){
      cells.push_back(vector<Cell*>());
      for(int x=0; x<(int)input[0].size(); x++){
        cells.back().push_back(new Cell((int)(input[y][x])-48, x, y, bestVal));
        if(y>0)
          cells[y][x]->connectNeighbours(cells[y-1][x], Dir::up);
        if(x>0)
          cells[y][x]->connectNeighbours(cells[y][x-1], Dir::left);
      }
    }
    cells.back().back()->finalCell(true);
    cells.front().front()->evaluateCart2(Dir::right, 0, 0, true);
    cout << "part 2: " << *bestVal << endl;
  }
}
