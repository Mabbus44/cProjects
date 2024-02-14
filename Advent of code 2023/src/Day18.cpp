#include "Day18.h"

Square::Square(){
  _color = "";
  _dug = false;
  _edge = false;
  _checked = false;
}

void Square::output(){
  if(_dug)
    cout << "#";
  else
    cout << ".";
}

void Square::dig(string color, bool edge){
  _dug = true;
  _edge = edge;
  _color = color;
}

void Instruction::load(string hex){
  if(hex.back() == '0')
    _dir = Dir::right;
  else if(hex.back() == '1')
    _dir = Dir::down;
  else if(hex.back() == '2')
    _dir = Dir::left;
  else if(hex.back() == '3')
    _dir = Dir::up;
  else
    cout << "Error: last letter in hex not 0-3" << endl;
  int mul = 1;
  _length = 0;
  for(int i=hex.length()-2; i>=0; i--){
    int asciiCode = (int)hex[i];
    if(asciiCode >= 48 && asciiCode <=57){
      _length += (asciiCode-48)*mul;
    }else if(asciiCode >= 97 && asciiCode <=102){
      _length += (asciiCode-87)*mul;
    }else{
      cout << "Error: hex digit not 0-9 or a-f" << endl;
    }
    mul *= 16;
  }
}

Day18::Day18()
{
  //ctor
}

Day18::~Day18()
{
  //dtor
}

void Day18::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> input = loader.toVectorStr2d({" ", "(", ")"});
  resetGround();
  for(vector<string> instruction: input){
    digMany(instruction[0], InputLoader::toSingleInt(instruction[1]), instruction[2]);
  }
  addLineUp();
  addLineDown();
  addLineLeft();
  addLineRight();
  checkSquare(0,0);
  digAllUnchecked();
  cout << "part 1: " << countHoles() << endl;
}

void Day18::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> input = loader.toVectorStr2d({" ", "(#", ")"});
  vector<Instruction> instructions;
  for(vector<string> row: input)
    instructions.push_back(Instruction(row[2]));
  int sumHor = 0;
  int sumVer = 0;
  for(int i=0; i<(int)instructions.size(); i++){
    int lastId = i-1;
    int nextId = i+1;
    if(i == 0)
      lastId = (int)instructions.size() - 1;
    if(i == (int)instructions.size()-1)
      nextId = 0;
    if(instructions[i].dir() % 2 == 0) // Right/left
      instructions[i].swapDir(true);
    else
      instructions[i].swapDir(instructions[lastId].dir() == instructions[nextId].dir());
  }
  cout << "part 2: " << sumHor << " " << sumVer << endl;
}

void Day18::resetGround(){
  _minX = 0;
  _minY = 0;
  _posX = 0;
  _posY = 0;
  for(vector<Square*> row: _ground){
    for(Square* s: row){
      delete s;
    }
  }
  _ground.clear();
  _ground = {{new Square()}};
}

void Day18::digMany(string dir, int len, string color){
  for(int i=0; i<len; i++){
    if(dir == "R"){
      _posX++;
    }else if(dir == "L"){
      _posX--;
    }else if(dir == "U"){
      _posY--;
    }else if(dir == "D"){
      _posY++;
    }else{
      cout << "Error: Invalid dir in digMany()";
    }
    digOne(_posX, _posY, color);
  }
}

void Day18::digOne(int x, int y, string color){
  if(x < _minX)
    addLineLeft();
  if(x >= _minX + (int)_ground[0].size())
    addLineRight();
  if(y < _minY)
    addLineUp();
  if(y >= _minY + (int)_ground.size())
    addLineDown();
  _ground[y-_minY][x-_minX]->dig(color);
}

void Day18::addLineLeft(){
  for(vector<Square*>& row: _ground)
    row.insert(row.begin(), new Square());
  _minX--;
}

void Day18::addLineRight(){
  for(vector<Square*>& row: _ground)
    row.push_back(new Square());
}

void Day18::addLineUp(){
  vector<Square*> newRow(_ground[0].size());
  for(int i=0; i<(int)_ground[0].size(); i++)
    newRow[i] = new Square();
  _ground.insert(_ground.begin(), newRow);
  _minY--;
}

void Day18::addLineDown(){
  vector<Square*> newRow(_ground[0].size());
  for(int i=0; i<(int)_ground[0].size(); i++)
    newRow[i] = new Square();
  _ground.push_back(newRow);
}

void Day18::output(int part){
  int startId = 0;
  int endId = (int)_ground[0].size();
  if(part == 1){
    endId = endId/2;
  }else if(part == 2){
    startId = endId/2;
  }
  for(vector<Square*> row:_ground){
    for(int id=startId; id<endId; id++)
      row[id]->output();
    cout << endl;
  }
}

void Day18::checkSquare(int x, int y, int depth){
  int xSize = (int)_ground[0].size();
  int ySize = (int)_ground.size();
  deque<tuple<int,int>> checkList;
  checkList.push_back(make_tuple(y, x));
  _ground[y][x]->checked(true);
  while((int)checkList.size() > 0){
    int cy=get<0>(checkList.front());
    int cx=get<1>(checkList.front());
    for(int ax=cx-1; ax<=cx+1; ax++){
      for(int ay=cy-1; ay<=cy+1; ay++){
        if((ax == cx) != (ay == cy) && !(ax < 0 || ay < 0 || ax >= xSize || ay >= ySize || _ground[ay][ax]->checked() || _ground[ay][ax]->dug())){
          _ground[ay][ax]->checked(true);
          checkList.push_back(make_tuple(ay, ax));
        }
      }
    }
    checkList.pop_front();
  }
}

void Day18::digAllUnchecked(){
  for(vector<Square*> row: _ground){
    for(Square* s: row){
      if(!s->dug() && !s->checked())
        s->dug(true);
    }
  }
}

int Day18::countHoles(){
  int sum=0;
  for(vector<Square*> row: _ground)
    for(Square* s: row)
      if(s->dug())
        sum++;
  return sum;
}
