#include "Day08.h"
#include <list>

Day08::Day08()
{
  //ctor
}

Day08::~Day08()
{
  //dtor
}

void Day08::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  vector<vector<Tree>> trees;
  int y = 0;
  for(vector<char> inputRow: input){
    vector<Tree> treeRow;
    int x = 0;
    for(char i: inputRow){
      treeRow.push_back(Tree((int)i - 48, x, y));
      x++;
    }
    trees.push_back(treeRow);
    y++;
  }
  for(y=0; y<99; y++){
    int biggestTree = -1;
    for(int x=0; x<99; x++){
      trees[y][x].highestW = biggestTree;
      biggestTree = max(biggestTree, trees[y][x].height);
    }
    biggestTree = -1;
    for(int x=98; x>=0; x--){
      trees[y][x].highestE = biggestTree;
      biggestTree = max(biggestTree, trees[y][x].height);
    }
  }
  for(int x=0; x<99; x++){
    int biggestTree = -1;
    for(int y=0; y<99; y++){
      trees[y][x].highestS = biggestTree;
      biggestTree = max(biggestTree, trees[y][x].height);
    }
    biggestTree = -1;
    for(y=98; y>=0; y--){
      trees[y][x].highestN = biggestTree;
      biggestTree = max(biggestTree, trees[y][x].height);
    }
  }
  int visCount = 0;
  for(int x=0; x<99; x++){
    for(y=0; y<99; y++){
      if(trees[y][x].isVisible())
        visCount++;
    }
  }
  cout << "part 1: " << visCount << endl;
}

void Day08::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> input = loader.toVectorChar2d();
  vector<vector<Tree>> trees;
  int y = 0;
  for(vector<char> inputRow: input){
    vector<Tree> treeRow;
    int x = 0;
    for(char i: inputRow){
      treeRow.push_back(Tree((int)i - 48, x, y));
      x++;
    }
    trees.push_back(treeRow);
    y++;
  }
  for(y=0; y<99; y++){
    list<Tree*> viewingTrees;
    for(int x=0; x<99; x++){
      list<Tree*>::iterator it = viewingTrees.begin();
      while (it != viewingTrees.end()){
        if((*it)->height <= trees[y][x].height){
          (*it)->viewDistanceE = trees[y][x].x - (*it)->x;
          viewingTrees.erase(it++);
        }else{
          it++;
        }
      }
      viewingTrees.push_back(&(trees[y][x]));
    }
    list<Tree*>::iterator it = viewingTrees.begin();
    while (it != viewingTrees.end()){
      (*it)->viewDistanceE = 98 - (*it)->x;
      it++;
    }
    viewingTrees.clear();

    for(int x=98; x>=0; x--){
      it = viewingTrees.begin();
      while (it != viewingTrees.end()){
        if((*it)->height <= trees[y][x].height){
          (*it)->viewDistanceW = (*it)->x - trees[y][x].x;
          viewingTrees.erase(it++);
        }else{
          it++;
        }
      }
      viewingTrees.push_back(&(trees[y][x]));
    }
    it = viewingTrees.begin();
    while (it != viewingTrees.end()){
      (*it)->viewDistanceW = (*it)->x;
      it++;
    }
  }

  for(int x=0; x<99; x++){
    list<Tree*> viewingTrees;
    for(int y=0; y<99; y++){
      list<Tree*>::iterator it = viewingTrees.begin();
      while (it != viewingTrees.end()){
        if((*it)->height <= trees[y][x].height){
          (*it)->viewDistanceS = trees[y][x].y - (*it)->y;
          viewingTrees.erase(it++);
        }else{
          it++;
        }
      }
      viewingTrees.push_back(&(trees[y][x]));
    }
    list<Tree*>::iterator it = viewingTrees.begin();
    while (it != viewingTrees.end()){
      (*it)->viewDistanceS = 98 - (*it)->y;
      it++;
    }
    viewingTrees.clear();

    for(int y=98; y>=0; y--){
      it = viewingTrees.begin();
      while (it != viewingTrees.end()){
        if((*it)->height <= trees[y][x].height){
          (*it)->viewDistanceN = (*it)->y - trees[y][x].y;
          viewingTrees.erase(it++);
        }else{
          it++;
        }
      }
      viewingTrees.push_back(&(trees[y][x]));
    }
    it = viewingTrees.begin();
    while (it != viewingTrees.end()){
      (*it)->viewDistanceN = (*it)->y;
      it++;
    }
  }
  int maxScore = 0;
  for(int x=0; x<99; x++){
    for(y=0; y<99; y++){
      if(trees[y][x].score()>maxScore)
        maxScore = trees[y][x].score();
    }
  }
  cout << "part 2: " << maxScore << endl;
}
