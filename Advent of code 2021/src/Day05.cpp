#include "Day05.h"

Day05::Day05()
{
  //ctor
}

Day05::~Day05()
{
  //dtor
}

void Day05::part1(string filename){
  InputLoader loader(filename);
  vector<vector<int>> vvi = loader.toVectorInt2d({",", "->"});
  vector<Line> lines;
  Grid grid;
  for(vector<int> vi: vvi){
    Line l;
    l.loadInput(vi);
    lines.push_back(l);
  }
  grid.init(1001);
  grid.setGrid(lines);
  int intersections = grid.getIntersections();
  cout << "Part 1: " << intersections << endl;
}

void Day05::part2(string filename){
  InputLoader loader(filename);
  vector<vector<int>> vvi = loader.toVectorInt2d({",", "->"});
  vector<Line> lines;
  Grid grid;
  for(vector<int> vi: vvi){
    Line l;
    l.loadInput(vi);
    lines.push_back(l);
  }
  grid.init(1001);
  grid.setGrid(lines, true);
  int intersections = grid.getIntersections();
  cout << "Part 2: " << intersections << endl;
}

void Line::loadInput(vector<int> input){
  if(input.size()<4){
    cout << "error: to few inputs to form a line" << endl;
    return;
  }
  x1=input[0];
  y1=input[1];
  x2=input[2];
  y2=input[3];
}

void Line::output(){
  cout << "(" << x1 << ", " << y1 << ")-(" << x2 << ", " << y2 << ")" << endl;
}

void Grid::init(int gridSize){
  this->gridSize = gridSize;
  for(int row=0; row<gridSize; row++){
    vector<int> vi;
    grid.push_back(vi);
    for(int col=0; col<gridSize; col++){
      grid[row].push_back(0);
    }
  }
}

void Grid::setGrid(vector<Line>& lines, bool countDiagonal){
  for(Line l:lines){
    if(l.x1==l.x2){
      if(l.y1<=l.y2){
        for(int y=l.y1; y<=l.y2; y++){
          grid[y][l.x1]++;
        }
      }else{
        for(int y=l.y2; y<=l.y1; y++){
          grid[y][l.x1]++;
        }
      }
    }else if(l.y1==l.y2){
      if(l.x1<=l.x2){
        for(int x=l.x1; x<=l.x2; x++){
          grid[l.y1][x]++;
        }
      }else{
        for(int x=l.x2; x<=l.x1; x++){
          grid[l.y1][x]++;
        }
      }
    }else if(countDiagonal){
      int steps = abs(l.x2-l.x1);
      int xDir = 1;
      int yDir = 1;
      if(l.x1>l.x2)
        xDir = -1;
      if(l.y1>l.y2)
        yDir = -1;
      for(int i=0; i<=steps; i++){
        grid[l.y1+yDir*i][l.x1+xDir*i]++;
      }
    }
  }
}

int Grid::getIntersections(){
  int intersections = 0;
  for(int row=0; row<gridSize; row++){
    for(int col=0; col<gridSize; col++){
      if(grid[row][col]>1)
        intersections++;
    }
  }
  return intersections;
}

void Grid::output(){
  for(int row=0; row<gridSize; row++){
    for(int col=0; col<gridSize; col++){
      cout << grid[row][col];
    }
    cout << endl;
  }
}
