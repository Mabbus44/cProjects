#include "Day11.h"

int Day11::occupiedNeighbours(int x, int y){
  int sum=0;
  for(int dx=x-1; dx<=x+1; dx++){
    for(int dy=y-1; dy<=y+1; dy++){
      if(!(dx==x && dy==y) && dx>=0 && dy>=0 && dx<(int)seats[0].size() && dy<(int)seats.size() && seats[dy][dx] == '#'){
        sum++;
      }
    }
  }
  return sum;
}

int Day11::occupiedNeighboursPart2(int x, int y){
  int sum=0;
  for(int dx=-1; dx<=1; dx++){
    for(int dy=-1; dy<=1; dy++){
      int cX = x+dx;
      int cY = y+dy;
      while(!(dx==0 && dy==0) && cX>=0 && cY>=0 && cX<(int)seats[0].size() && cY<(int)seats.size() && seats[cY][cX] == '.'){
        cX += dx;
        cY += dy;
      }
      if(!(dx==0 && dy==0) && cX>=0 && cY>=0 && cX<(int)seats[0].size() && cY<(int)seats.size() && seats[cY][cX] == '#'){
        sum++;
      }
    }
  }
  return sum;
}

void Day11::output(){
  for(int y=0; y<(int)seats.size(); y++){
    for(int x=0; x<(int)seats[0].size(); x++){
      cout << seats[y][x];
    }
    cout << endl;
  }
}

Day11::Day11()
{
  //ctor
}

Day11::~Day11()
{
  //dtor
}

void Day11::part1(string filename){
  InputLoader loader(filename);
  seats = loader.toVectorChar2d();
  newSeats = seats;
  bool changed=true;
  while(changed){
    changed = false;
    for(int y=0; y<(int)seats.size(); y++){
      for(int x=0; x<(int)seats[0].size(); x++){
        if(seats[y][x] == 'L'){
          if(occupiedNeighbours(x,y)==0){
            newSeats[y][x] = '#';
            changed = true;
          }
          else
            newSeats[y][x] = 'L';
        }else if(seats[y][x] == '#'){
          if(occupiedNeighbours(x,y)>=4){
            newSeats[y][x] = 'L';
            changed = true;
          }
          else
            newSeats[y][x] = '#';
        }else
          newSeats[y][x] = '.';
      }
    }
    seats = newSeats;
  }
  int occCount = 0;
  for(int y=0; y<(int)seats.size(); y++){
    for(int x=0; x<(int)seats[0].size(); x++){
      if(seats[y][x] == '#')
        occCount++;
    }
  }
  cout << "part 1: " << occCount << endl;
}

void Day11::part2(string filename){
  InputLoader loader(filename);
  seats = loader.toVectorChar2d();
  newSeats = seats;
  bool changed=true;
  int occCount = 0;
  int a, b;
  bool saveB = false;
  while(changed){
    changed = false;
    for(int y=0; y<(int)seats.size(); y++){
      for(int x=0; x<(int)seats[0].size(); x++){
        if(seats[y][x] == 'L'){
          if(occupiedNeighboursPart2(x,y)==0){
            newSeats[y][x] = '#';
            changed = true;
          }
          else
            newSeats[y][x] = 'L';
        }else if(seats[y][x] == '#'){
          if(occupiedNeighboursPart2(x,y)>=5){
            newSeats[y][x] = 'L';
            changed = true;
          }
          else
            newSeats[y][x] = '#';
        }else
          newSeats[y][x] = '.';
      }
    }
    seats = newSeats;
    occCount = 0;
    for(int y=0; y<(int)seats.size(); y++){
      for(int x=0; x<(int)seats[0].size(); x++){
        if(seats[y][x] == '#')
          occCount++;
      }
    }
    if(saveB)
      b=occCount;
    else
      a=occCount;
    saveB = !saveB;
    if(false && a==6363){
      cout << endl << endl;
      output();
    }
    cout << a << " " << b << endl;

  }
  cout << "part 2: " << occCount << endl;}
