#include "Day09.h"

Day09::Day09()
{
  //ctor
}

Day09::~Day09()
{
  //dtor
}

void Day09::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> inputs = loader.toVectorStr2d({" "});
  vector<Command> commands;
  for(vector<string> input: inputs)
    commands.push_back(Command(input[0], stoi(input[1])));
  tailHistory.clear();
  tailHistory.val = "0,0";
  x=0; y=0; tailX=0; tailY=0;
  for(Command c: commands)
    executeCommand(c);
  int ans = tailHistory.count();
  cout << "part 1: " << ans << endl;
}

void Day09::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> inputs = loader.toVectorStr2d({" "});
  vector<Command> commands;
  for(vector<string> input: inputs)
    commands.push_back(Command(input[0], stoi(input[1])));
  tailHistory.clear();
  tailHistory.val = "0,0";
  x=0; y=0;
  for(int i=0; i<9; i++){
    tail2X[i] = 0;
    tail2Y[i] = 0;
  }
  for(Command c: commands)
    executeCommand2(c);
  int ans = tailHistory.count();
  cout << "part 2: " << ans << endl;
}

void Day09::executeCommand(Command c){
  switch(c.dir){
    case RIGHT:
      x+=c.steps;
      break;
    case LEFT:
      x-=c.steps;
      break;
    case UPP:
      y+=c.steps;
      break;
    case DOWN:
      y-=c.steps;
      break;
  }
  while(abs(x-tailX)>1 || abs(y-tailY)>1)
    moveTail();
}

void Day09::moveTail(){
  if(abs(x-tailX)<=1 && abs(y-tailY)<=1)
    return;
  if(x!=tailX && y!=tailY){
    if(x>tailX)
      tailX++;
    else
      tailX--;
    if(y>tailY)
      tailY++;
    else
      tailY--;
    tailHistory.insert(to_string(tailX)+","+to_string(tailY));
    return;
  }
  if(x>tailX+1)
    tailX++;
  if(x<tailX-1)
    tailX--;
  if(y>tailY+1)
    tailY++;
  if(y<tailY-1)
    tailY--;
  tailHistory.insert(to_string(tailX)+","+to_string(tailY));
}

void Day09::executeCommand2(Command c){
  for(int i=0; i<c.steps; i++){
    switch(c.dir){
      case RIGHT:
        x++;
        break;
      case LEFT:
        x--;
        break;
      case UPP:
        y++;
        break;
      case DOWN:
        y--;
        break;
    }
    while(abs(x-tail2X[0])>1 || abs(y-tail2Y[0])>1)
      moveTail2(0, x, y);
    for(int i=1; i<9; i++)
      while(abs(tail2X[i-1]-tail2X[i])>1 || abs(tail2Y[i-1]-tail2Y[i])>1)
        moveTail2(i, tail2X[i-1], tail2Y[i-1]);
  }
}

void Day09::moveTail2(int tailId, int followX, int followY){
  if(abs(followX-tail2X[tailId])<=1 && abs(followY-tail2Y[tailId])<=1)
    return;
  if(followX!=tail2X[tailId] && followY!=tail2Y[tailId]){
    if(followX>tail2X[tailId])
      tail2X[tailId]++;
    else
      tail2X[tailId]--;
    if(followY>tail2Y[tailId])
      tail2Y[tailId]++;
    else
      tail2Y[tailId]--;
    if(tailId == 8){
      //cout << to_string(tail2X[tailId])+","+to_string(tail2Y[tailId]) << endl;
      tailHistory.insert(to_string(tail2X[tailId])+","+to_string(tail2Y[tailId]));
    }
    return;
  }
  if(followX>tail2X[tailId]+1)
    tail2X[tailId]++;
  if(followX<tail2X[tailId]-1)
    tail2X[tailId]--;
  if(followY>tail2Y[tailId]+1)
    tail2Y[tailId]++;
  if(followY<tail2Y[tailId]-1)
    tail2Y[tailId]--;
  if(tailId == 8){
    //cout << to_string(tail2X[tailId])+","+to_string(tail2Y[tailId]) << endl;
    tailHistory.insert(to_string(tail2X[tailId])+","+to_string(tail2Y[tailId]));
  }
}

void Command::load(string dir, int steps){
  if(dir.compare("R") == 0)
    this->dir = RIGHT;
  else if(dir.compare("L") == 0)
    this->dir = LEFT;
  else if(dir.compare("U") == 0)
    this->dir = UPP;
  else if(dir.compare("D") == 0)
    this->dir = DOWN;
  else
    cout << "ERROR: " << dir << "is not a valid direction" << endl;
  this->steps = steps;
}
