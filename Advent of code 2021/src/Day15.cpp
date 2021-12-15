#include "Day15.h"

Day15::Day15()
{
  //ctor
}

Day15::~Day15()
{
  //dtor
}

void Day15::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  for(int y=0; y<100; y++){
    for(int x=0; x<100; x++){
      rooms[y][x].risk = (int)(vvc[y][x])-48;
    }
  }
  debugX=-1;
  debugY=-1;
  rooms[0][0].lowestRisk = rooms[0][0].risk;
  rooms[0][0].lowestRiskCalculated = true;
  for(int column=1; column<100; column++){
    for(int y=0; y<=column; y++)
      setLowestRisk(y, column);
    for(int x=0; x<column; x++)
      setLowestRisk(column, x);
  }
  //drawLowestRisk();
  cout << "Part 1: " << rooms[99][99].lowestRisk - rooms[0][0].risk << endl;
}

void Day15::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  for(int y=0; y<100; y++){
    for(int x=0; x<100; x++){
      rooms[y][x].risk = (int)(vvc[y][x])-48;
      for(int tileX=0; tileX<5; tileX++){
        for(int tileY=0; tileY<5; tileY++){
          lowestRiskCalculated[y+100*tileY][x+100*tileX] = false;
        }
      }
    }
  }
  debugX=-1;
  debugY=-1;
  lowestRisk[0][0] = rooms[0][0].risk;
  lowestRiskCalculated[0][0] = true;
  for(int column=1; column<500; column++){
    for(int y=0; y<=column; y++)
      setLowestRiskPart2(y, column);
    for(int x=0; x<column; x++)
      setLowestRiskPart2(column, x);
  }
  cout << "Part 2: " << lowestRisk[499][499] - getRisk(0,0) << endl;
}

int Day15::getRisk(int y, int x){
  int tileX=0;
  int tileY=0;
  while(x>=100){
    tileX++;
    x-=100;
  }
  while(y>=100){
    tileY++;
    y-=100;
  }
  int ans = rooms[y][x].risk+tileX+tileY;
  if(ans>9)
    ans-=9;
  return ans;
}

void Day15::crawl(int y, int x, int newRisk){
  rooms[y][x].lowestRisk = newRisk;
  if(x==debugX && y==debugY)
    cout << "Crawl start " << rooms[debugY][debugX].lowestRisk << endl;
  if(x<99 && rooms[y][x+1].lowestRiskCalculated && rooms[y][x].lowestRisk+rooms[y][x+1].risk < rooms[y][x+1].lowestRisk)
    crawl(y, x+1, rooms[y][x].lowestRisk+rooms[y][x+1].risk);
  if(y<99 && rooms[y+1][x].lowestRiskCalculated && rooms[y][x].lowestRisk+rooms[y+1][x].risk < rooms[y+1][x].lowestRisk)
    crawl(y+1, x, rooms[y][x].lowestRisk+rooms[y+1][x].risk);
  if(x>0 && rooms[y][x-1].lowestRiskCalculated && rooms[y][x].lowestRisk+rooms[y][x-1].risk < rooms[y][x-1].lowestRisk)
    crawl(y, x-1, rooms[y][x].lowestRisk+rooms[y][x-1].risk);
  if(y>0 && rooms[y-1][x].lowestRiskCalculated && rooms[y][x].lowestRisk+rooms[y-1][x].risk < rooms[y-1][x].lowestRisk)
    crawl(y-1, x, rooms[y][x].lowestRisk+rooms[y-1][x].risk);
  if(x==debugX && y==debugY)
    cout << "Crawl end " << rooms[debugY][debugX].lowestRisk << endl;
}

void Day15::crawlPart2(int y, int x, int newRisk){
  lowestRisk[y][x] = newRisk;
  if(x==debugX && y==debugY)
    cout << "Crawl start " << lowestRisk[debugY][debugX] << endl;
  if(x<499 && lowestRiskCalculated[y][x+1] && lowestRisk[y][x]+getRisk(y, x+1) < lowestRisk[y][x+1])
    crawlPart2(y, x+1, lowestRisk[y][x]+getRisk(y,x+1));
  if(y<499 && lowestRiskCalculated[y+1][x] && lowestRisk[y][x]+getRisk(y+1,x) < lowestRisk[y+1][x])
    crawlPart2(y+1, x, lowestRisk[y][x]+getRisk(y+1,x));
  if(x>0 && lowestRiskCalculated[y][x-1] && lowestRisk[y][x]+getRisk(y, x-1) < lowestRisk[y][x-1])
    crawlPart2(y, x-1, lowestRisk[y][x]+getRisk(y,x-1));
  if(y>0 && lowestRiskCalculated[y-1][x] && lowestRisk[y][x]+getRisk(y-1, x) < lowestRisk[y-1][x])
    crawlPart2(y-1, x, lowestRisk[y][x]+getRisk(y-1,x));
  if(x==debugX && y==debugY)
    cout << "Crawl end " << lowestRisk[debugY][debugX] << endl;
}

void Day15::drawLowestRisk(){
  for(int y=0; y<100; y++){
    for(int x=0; x<100; x++){
      cout << rooms[y][x].lowestRisk << " ";
    }
    cout << endl;
  }
}

void Day15::setLowestRisk(int y, int x){
  if(x==debugX && y==debugY)
    cout << "Lowest risk start " << rooms[debugY][debugX].lowestRisk << endl;
  if(x<99 && rooms[y][x+1].lowestRiskCalculated && (rooms[y][x+1].lowestRisk+rooms[y][x].risk < rooms[y][x].lowestRisk || !rooms[y][x].lowestRiskCalculated)){
    rooms[y][x].lowestRisk = rooms[y][x+1].lowestRisk + rooms[y][x].risk;
    rooms[y][x].lowestRiskCalculated = true;
  }
  if(y<99 && rooms[y+1][x].lowestRiskCalculated && (rooms[y+1][x].lowestRisk+rooms[y][x].risk < rooms[y][x].lowestRisk || !rooms[y][x].lowestRiskCalculated)){
    rooms[y][x].lowestRisk = rooms[y+1][x].lowestRisk + rooms[y][x].risk;
    rooms[y][x].lowestRiskCalculated = true;
  }
  if(x>0 && rooms[y][x-1].lowestRiskCalculated && (rooms[y][x-1].lowestRisk+rooms[y][x].risk < rooms[y][x].lowestRisk || !rooms[y][x].lowestRiskCalculated)){
    rooms[y][x].lowestRisk = rooms[y][x-1].lowestRisk + rooms[y][x].risk;
    rooms[y][x].lowestRiskCalculated = true;
  }
  if(y>0 && rooms[y-1][x].lowestRiskCalculated && (rooms[y-1][x].lowestRisk+rooms[y][x].risk < rooms[y][x].lowestRisk || !rooms[y][x].lowestRiskCalculated)){
    rooms[y][x].lowestRisk = rooms[y-1][x].lowestRisk + rooms[y][x].risk;
    rooms[y][x].lowestRiskCalculated = true;
  }
  if(!rooms[y][x].lowestRiskCalculated){
    cout << "ERRRORR" << endl;
    return;
  }
  if(x==debugX && y==debugY)
    cout << "Lowest risk before crawl " << rooms[debugY][debugX].lowestRisk << endl;
  crawl(y, x, rooms[y][x].lowestRisk);
}

void Day15::setLowestRiskPart2(int y, int x){
  if(x==debugX && y==debugY)
    cout << "Lowest risk start " << lowestRisk[debugY][debugX] << endl;
  int roomRisk = getRisk(y, x);
  if(x<499 && lowestRiskCalculated[y][x+1] && (lowestRisk[y][x+1]+roomRisk < lowestRisk[y][x] || !lowestRiskCalculated[y][x])){
    lowestRisk[y][x] = lowestRisk[y][x+1] + roomRisk;
    lowestRiskCalculated[y][x] = true;
  }
  if(y<499 && lowestRiskCalculated[y+1][x] && (lowestRisk[y+1][x]+roomRisk < lowestRisk[y][x] || !lowestRiskCalculated[y][x])){
    lowestRisk[y][x] = lowestRisk[y+1][x] + roomRisk;
    lowestRiskCalculated[y][x] = true;
  }
  if(x>0 && lowestRiskCalculated[y][x-1] && (lowestRisk[y][x-1]+roomRisk < lowestRisk[y][x] || !lowestRiskCalculated[y][x])){
    lowestRisk[y][x] = lowestRisk[y][x-1] + roomRisk;
    lowestRiskCalculated[y][x] = true;
  }
  if(y>0 && lowestRiskCalculated[y-1][x] && (lowestRisk[y-1][x]+roomRisk < lowestRisk[y][x] || !lowestRiskCalculated[y][x])){
    lowestRisk[y][x] = lowestRisk[y-1][x] + roomRisk;
    lowestRiskCalculated[y][x] = true;
  }
  if(!lowestRiskCalculated[y][x]){
    cout << "ERRRORR" << endl;
    return;
  }
  if(x==debugX && y==debugY)
    cout << "Lowest risk before crawl " << lowestRisk[debugY][debugX] << endl;
  crawlPart2(y, x, lowestRisk[y][x]);
}
