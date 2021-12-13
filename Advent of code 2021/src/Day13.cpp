#include "Day13.h"

Day13::Day13()
{
  //ctor
}

Day13::~Day13()
{
  //dtor
}

void Day13::loadInput(string fileName){
  InputLoader loader(fileName);
  vector<vector<string>> vvs = loader.toVectorStr2d({",", "fold along ", "="});
  bool loadingCoords=true;
  for(vector<string> vs: vvs){
    if(vs.size()==0)
      loadingCoords = false;
    else if(loadingCoords)
      coords.push_back(Coord(stoi(vs[0]), stoi(vs[1])));
    else{
      if(vs[0]=="x")
        instructions.push_back(Instruction(X, stoi(vs[1])));
      else
        instructions.push_back(Instruction(Y, stoi(vs[1])));
    }
  }
}

void Day13::removeDuplicateDots(){
  for(int i=0; i<(int)coords.size(); i++){
    for(int i2=i+1; i2<(int)coords.size(); i2++){
      if(coords[i] == coords[i2])
        coords.erase(coords.begin()+i2);
    }
  }
}

void Day13::fold(Instruction inst){
  for(int i=0; i<(int)coords.size(); i++){
    if(inst.dir==X){
      if(coords[i].x>inst.row)
        coords[i].x = inst.row - (coords[i].x-inst.row);
    }
    else{
      if(coords[i].y>inst.row)
        coords[i].y = inst.row - (coords[i].y-inst.row);
    }
  }
}

void Day13::part1(string filename){
  loadInput(filename);
  /*for(vector<string> vs:vvs){
    for(string v:vs)
      cout << v << ",";
    cout << vs.size() << endl;
  }*/
  /*for(Coord c: coords)
    cout << c.x << "," << c.y << endl;
  cout << endl;
  for(Instruction i: instructions)
    cout << i.dir << "," << i.row << endl;*/
  fold(instructions[0]);
  removeDuplicateDots();
  cout << "Part 1: " << coords.size() << endl;
  coords.clear();
  instructions.clear();
}

void Day13::part2(string filename){
  loadInput(filename);
  for(Instruction i: instructions){
    fold(i);
    removeDuplicateDots();
  }
  int xMin =999999;
  int yMin =999999;
  int xMax =0;
  int yMax =0;
  for(Coord c: coords){
    if(c.x<xMin)
      xMin=c.x;
    if(c.y<yMin)
      yMin=c.y;
    if(c.x>xMax)
      xMax=c.x;
    if(c.y>yMax)
      yMax=c.y;
  }
  bool grid[xMax-xMin+1][yMax-yMin+1];
  for(int x=xMin; x<=xMax; x++){
    for(int y=yMin; y<=yMax; y++){
      grid[x][y] = 0;
    }
  }
  for(Coord c: coords)
    grid[c.x][c.y] = true;
  cout << "Part 2: " << endl;
  for(int y=yMin; y<=yMax; y++){
    for(int x=xMin; x<=xMax; x++){
      if(grid[x][y])
        cout << "*";
      else
        cout << " ";
    }
    cout << endl;
  }
}
