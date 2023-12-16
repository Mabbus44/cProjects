#include "Day10.h"

Day10::Day10()
{
  //ctor
}

Day10::~Day10()
{
  //dtor
}

void Day10::part1(string filename){
  InputLoader loader(filename);
  _map = loader.toVectorChar2d();
  findStart();
    _steps = 1;
  if(_posY>0 && (_map[_posY-1][_posX] == '|' || _map[_posY-1][_posX] == '7' || _map[_posY-1][_posX] == 'F')){
    _lastDir = Dir::up;
    _moves.push_back(Move(_posX, _posY, _lastDir, 0));
    _posY--;
  }else if(_posY<(int)_map.size()-1 && (_map[_posY+1][_posX] == '|' || _map[_posY+1][_posX] == 'L' || _map[_posY+1][_posX] == 'J')){
    _lastDir = Dir::down;
    _moves.push_back(Move(_posX, _posY, _lastDir, 0));
    _posY++;
  }else if(_posX>0 && (_map[_posY][_posX-1] == '-' || _map[_posY][_posX-1] == 'L' || _map[_posY][_posX-1] == 'F')){
    _lastDir = Dir::left;
    _moves.push_back(Move(_posX, _posY, _lastDir, 0));
    _posX--;
  }else if(_posX<(int)_map[0].size()-1 && (_map[_posY][_posX+1] == '-' || _map[_posY][_posX+1] == 'J' || _map[_posY][_posX+1] == '7')){
    _lastDir = Dir::right;
    _moves.push_back(Move(_posX, _posY, _lastDir, 0));
    _posX++;
  }
  while(_map[_posY][_posX] != 'S'){
    oneStep();
  }
  int turnSum = 0;
  for(int i=0; i<(int)_moves.size(); i++)
    turnSum += _moves[i].turn;
  if(turnSum > 0)
    _turnDir = Dir::right;
  else
    _turnDir = Dir::left;
  int ans = 0;
  if(_steps % 2 == 1)
    ans = 1;
  ans += _steps / 2;
  cout << "part 1: " << ans << endl;
}

void Day10::part2(string filename){
  //Requires part1 to run before
  for(int i=0; i<(int)_moves.size(); i++)
    addEncircledPositions(_moves[i]);
  cout << "part 2: " << _encircledAreas.size() << endl;
}

void Day10::findStart(){
  for(int y=0; y<(int)_map.size(); y++){
    for(int x=0; x<(int)_map[0].size(); x++){
      if(_map[y][x] == 'S'){
        _posX = x;
        _posY = y;
        _steps = 0;
        return;
      }
    }
  }
  cout << "Error: Start not found" << endl;
}

bool Day10::oneStep(){
  char c = _map[_posY][_posX];
  Dir dirA, dirB;

  if(c == '|'){
    dirA = Dir::up;
    dirB = Dir::down;
  }
  if(c == '-'){
    dirA = Dir::left;
    dirB = Dir::right;
  }
  if(c == 'L'){
    dirA = Dir::up;
    dirB = Dir::right;
  }
  if(c == 'J'){
    dirA = Dir::left;
    dirB = Dir::up;
  }
  if(c == '7'){
    dirA = Dir::left;
    dirB = Dir::down;
  }
  if(c == 'F'){
    dirA = Dir::right;
    dirB = Dir::down;
  }
  if(c == '.'){
    cout << "Error: Trying to move from ." << endl;
    return false;
  }
  if(c == 'S'){
    cout << "Error: Trying to move from S" << endl;
    return false;
  }
  Dir moveDir;
  Dir fromDir;
  if(opposite(_lastDir) == dirA){
    moveDir = dirB;
    fromDir = dirA;
  }else if(opposite(_lastDir) == dirB){
    moveDir = dirA;
    fromDir = dirB;
  }else{
    cout << "Error: Moved in from invalid dir" << endl;
    return false;
  }
  _moves.push_back(Move(_posX, _posY, moveDir, calcTurn(fromDir, moveDir)));
  if(moveDir == Dir::left)
    _posX--;
  if(moveDir == Dir::right)
    _posX++;
  if(moveDir == Dir::up)
    _posY--;
  if(moveDir == Dir::down)
    _posY++;
  if(_posX < 0 || _posY < 0 || _posX >= (int)_map[0].size() || _posY >= (int)_map.size()){
    cout << "Error: outside of map " << _posX << " " << _posY << endl;
    return false;
  }
  _steps++;
  _lastDir = moveDir;
  return true;
}

bool Day10::isLastMoveValid(){
  return false;
}

Dir Day10::opposite(Dir dir){
  if(dir == Dir::left)
    return Dir::right;
  if(dir == Dir::right)
    return Dir::left;
  if(dir == Dir::up)
    return Dir::down;
  if(dir == Dir::down)
    return Dir::up;
  cout << "Error: no oposite of dir" << endl;
  return Dir::up;
}

int Day10::calcTurn(Dir inDir, Dir outDir){
  if(inDir == Dir::left){
    if(outDir == Dir::up)
      return -1;
    if(outDir == Dir::down)
      return 1;
    return 0;
  }
  if(inDir == Dir::right){
    if(outDir == Dir::down)
      return -1;
    if(outDir == Dir::up)
      return 1;
    return 0;
  }
  if(inDir == Dir::up){
    if(outDir == Dir::right)
      return -1;
    if(outDir == Dir::left)
      return 1;
    return 0;
  }
  if(inDir == Dir::down){
    if(outDir == Dir::left)
      return -1;
    if(outDir == Dir::right)
      return 1;
    return 0;
  }
  return 0;
}

void Move::output(){
  cout << posX << ", " << posY << ", " << dir << ", " << turn << endl;
}

bool Day10::addEncircledPos(int posX, int posY){
  for(Move& m: _moves){
    if(m.posX == posX && m.posY == posY)
      return false;
  }
  for(Pos& p: _encircledAreas){
    if(p.posX == posX && p.posY == posY)
      return false;
  }
  _encircledAreas.push_back(Pos{posX, posY});
  addEncircledPos(posX+1, posY);
  addEncircledPos(posX, posY+1);
  addEncircledPos(posX-1, posY);
  addEncircledPos(posX, posY-1);
  return true;
}

void Day10::addEncircledPositions(Move& m){
  Dir firstDir, secondDir;
  if(m.dir == Dir::up){
    if(_turnDir == Dir::right){
      firstDir = Dir::right;
      secondDir = Dir::down;
    }else{
      firstDir = Dir::left;
      secondDir = Dir::down;
    }
  }
  if(m.dir == Dir::right){
    if(_turnDir == Dir::right){
      firstDir = Dir::down;
      secondDir = Dir::left;
    }else{
      firstDir = Dir::up;
      secondDir = Dir::left;
    }
  }
  if(m.dir == Dir::down){
    if(_turnDir == Dir::right){
      firstDir = Dir::left;
      secondDir = Dir::up;
    }else{
      firstDir = Dir::right;
      secondDir = Dir::up;
    }
  }
  if(m.dir == Dir::left){
    if(_turnDir == Dir::right){
      firstDir = Dir::up;
      secondDir = Dir::right;
    }else{
      firstDir = Dir::down;
      secondDir = Dir::right;
    }
  }
  int dirCount = 0;
  if(m.turn == 1 && _turnDir == Dir::left)
    dirCount = 2;
  if(m.turn == -1 && _turnDir == Dir::right)
    dirCount = 2;
  if(m.turn == 0)
    dirCount = 1;
  if(dirCount > 0){
    if(firstDir == Dir::up)
      addEncircledPos(m.posX, m.posY-1);
    if(firstDir == Dir::right)
      addEncircledPos(m.posX+1, m.posY);
    if(firstDir == Dir::down)
      addEncircledPos(m.posX, m.posY+1);
    if(firstDir == Dir::left)
      addEncircledPos(m.posX-1, m.posY);
  }
  if(dirCount > 1){
    if(secondDir == Dir::up)
      addEncircledPos(m.posX, m.posY-1);
    if(secondDir == Dir::right)
      addEncircledPos(m.posX+1, m.posY);
    if(secondDir == Dir::down)
      addEncircledPos(m.posX, m.posY+1);
    if(secondDir == Dir::left)
      addEncircledPos(m.posX-1, m.posY);
  }
}
