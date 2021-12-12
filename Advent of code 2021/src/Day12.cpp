#include "Day12.h"

void Cave::addConnection(Cave* newConnection){
  for(Cave* c: connections)
    if(c==newConnection)
      return;
  connections.push_back(newConnection);
}

void Cave::output(){
  cout << name << " (" << type << ", " << visited << ")" <<  endl;
  for(Cave* c:connections)
    cout << "   " << c->name << endl;
}

int Cave::countPaths(){
  int paths=0;
  if(visited && (type == START || type==SMALL))
    return 0;
  if(type==END)
    return 1;
  visited = true;
  for(Cave* c:connections)
    paths += c->countPaths();
  visited = false;
  return paths;
}

int Cave::countPathsPart2(bool visitedTwice, string chain){
  chain = chain +"-"+ name;
  //cout << chain << " " << visited << " " << visitedTwice <<  endl;
  int paths=0;
  bool removeVisitedTwice = false;
  if(visited && (type == START || (type==SMALL && visitedTwice))){
    return 0;
  }
  if(type==END){
    return 1;
  }
  if(type==SMALL && visited){
    visitedTwice = true;
    removeVisitedTwice = true;
  }
  visited = true;
  for(Cave* c:connections)
    paths += c->countPathsPart2(visitedTwice, chain);
  visited = false;
  if(removeVisitedTwice){
    visitedTwice = false;
    visited = true;
  }
  return paths;
}

Day12::Day12()
{
  //ctor
}

Day12::~Day12()
{
  //dtor
}

void Day12::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> caveNames = loader.toVectorStr2d({"-"});
  for(vector<string> vs: caveNames){
    Cave* newCaveA = addCave(vs[0]);
    Cave* newCaveB = addCave(vs[1]);
    newCaveA->addConnection(newCaveB);
    newCaveB->addConnection(newCaveA);
  }
  resetVisited();
  int paths = startCave->countPaths();
  cout << "Part 1: " << paths << endl;
}

void Day12::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> caveNames = loader.toVectorStr2d({"-"});
  for(vector<string> vs: caveNames){
    Cave* newCaveA = addCave(vs[0]);
    Cave* newCaveB = addCave(vs[1]);
    newCaveA->addConnection(newCaveB);
    newCaveB->addConnection(newCaveA);
  }
  resetVisited();
  int paths = startCave->countPathsPart2(false, "");
  cout << "Part 2: " << paths << endl;
}

Cave* Day12::addCave(string newName){
  for(Cave* c: caves){
    if(c->name == newName)
      return c;
  }
  Cave* newCave = new Cave();
  newCave->name = newName;
  if(newName=="start"){
    newCave->type = START;
    startCave = newCave;
  }
  else if(newName=="end"){
    newCave->type = END;
    endCave = newCave;
  }
  else if((int)newName[0]<96){
    newCave->type = BIG;
  }
  else{
    newCave->type = SMALL;
  }
  caves.push_back(newCave);
  return newCave;
}

void Day12::resetVisited(){
  for(Cave* c:caves)
    c->visited = false;
}
