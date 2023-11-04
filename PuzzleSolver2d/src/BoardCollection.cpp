#include "BoardCollection.h"
#include <iostream>

BoardCollection::BoardCollection()
{
  //ctor
}

BoardCollection::~BoardCollection()
{
  //dtor
}

BoardCollection::BoardCollection(ifstream& file){
  if(file.peek() == 'e' || file.peek() == EOF)
    cout << "ERROR: Trying to load boardcollection from invalid stream" << endl;
  string line;
  while(file.peek() != 'e'){
    addBoard(new Board(file));
  }
  getline(file, line);
  connectNeighbours();
  calculateMovePoints();
  calculateBoardLists();
}

void BoardCollection::setStartingBoard(Board* startingBoard){
  for(Board* board: _boards){
    board->clear();
  }
  _boards.clear();
  _boards.push_back(startingBoard);
}

void BoardCollection::generateChildren(){
  int testId = 0;
  vector<Board*> newBoards;
  while(testId < (int)_boards.size()){
    newBoards = _boards[testId]->getNextSteps();
    for(Board* newBoard: newBoards){
      bool isUnique = true;
      for(int oldBoardId = 0; oldBoardId < (int)_boards.size() && isUnique; oldBoardId++){
        if((*(_boards[oldBoardId])) == (*newBoard)){
          isUnique = false;
          _boards[oldBoardId]->connectNeighbours(_boards[testId]);
        }
      }
      if(isUnique){
        _boards.push_back(newBoard);
        newBoard->connectNeighbours(_boards[testId]);
      }else{
        newBoard->clear();
        delete newBoard;
      }
    }
    testId++;
    if(testId % 100 == 0)
      cout << "Tested " << testId << " / " << _boards.size() << " (" << _boards.size() - testId << ")" << endl;
  }
  calculateMovePoints();
}

void BoardCollection::setStepsLeft(Board* goal){
  if(goal == nullptr)
    return;
  list<Board*>* toBeCalculated;
  list<Board*>* beingCalculated;
  list<Board*>* temp;
  beingCalculated = new list<Board*>;
  toBeCalculated = new list<Board*>;
  for(Board* b: _boards){
    if(b->matchGoal(goal))
      beingCalculated->push_back(b);
  }

  int stepsLeft = 0;
  while(beingCalculated->size() > 0){
    cout << stepsLeft << ": " << beingCalculated->size() << endl;
    for(Board* b: (*beingCalculated)){
      b->calculateStepsLeft(stepsLeft);
      b->addNeighboursWithoutStepsLeft(toBeCalculated);
    }
    beingCalculated->clear();
    temp = beingCalculated;
    beingCalculated = toBeCalculated;
    toBeCalculated = temp;
    stepsLeft++;
  }
  delete beingCalculated;
  delete toBeCalculated;
}

void BoardCollection::output(string tab){
  cout << tab << "Collection:" << endl;
  for(Board* p: _boards){
    p->output(tab + " ");
    cout << endl;
  }
}

string BoardCollection::getSaveString(){
  string ans = "";
  int i = 0;
  for(Board* b: _boards)
    b->id(i++);
  for(Board* b: _boards)
    ans.append(b->getSaveString());
  ans.append("e\n");
  return ans;
}

void BoardCollection::free(){
  for(Board* b: _boards){
    b->free();
    delete b;
  }
}

void BoardCollection::goal(Board* goal){
  for(Board* b: _boards){
    b->stepsLeft(-1);
  }
  setStepsLeft(goal);
  calculateBoardLists();
}

void BoardCollection::connectNeighbours(){
  for(Board* b: _boards)
    b->connectNeighbours(_boards);
}

void BoardCollection::addBoard(Board* board){
  _boards.push_back(board);
}

void BoardCollection::calculateMovePoints(){
  for(Board* b: _boards)
    b->calculateMovePoints();
}

void BoardCollection::calculateBoardLists(){
  if(_boards.size() == 0 || _boards[0]->stepsLeft() == -1)
    return;
  int biggestStepsLeft = 0;
  int biggestCount = 0;
  int goalCount = 0;
  for(Board* b: _boards){
    if(b->stepsLeft() == 0){
      goalCount++;
    }else if(b->stepsLeft() > biggestStepsLeft){
      biggestStepsLeft = b->stepsLeft();
      biggestCount = 1;
    }else if(b->stepsLeft() == biggestStepsLeft){
      biggestCount++;
    }
  }
  if(goalCount > 20)
    goalCount = 20;
  if(biggestCount > 20)
    biggestCount = 20;
  _goalBoards.resize(goalCount);
  _mostStepsBoards.resize(biggestCount);
  int goalId = 0;
  int biggestId = 0;
  for(Board* b: _boards){
    if(goalId < goalCount && b->stepsLeft() == 0){
      _goalBoards[goalId++] = b;
    }else if(biggestId < biggestCount && b->stepsLeft() == biggestStepsLeft){
      _mostStepsBoards[biggestId++] = b;
    }
  }
  cout << "biggestStepsLeft: " + to_string(biggestStepsLeft) + " biggestCount: " + to_string(biggestCount) + " goalCount: " + to_string(goalCount) << endl;
}

list<string> BoardCollection::startDescriptionList(){
  list<string> ans;
  Board* n = _boards[0];
  ans.push_back(to_string(n->id()) + ": " + to_string(n->stepsLeft()));
  return ans;
}

list<string> BoardCollection::goalDescriptionList(){
  list<string> ans;
  for(Board* n: _goalBoards)
    ans.push_back(to_string(n->id()) + ": " + to_string(n->stepsLeft()));
  return ans;
}

list<string> BoardCollection::mostDescriptionList(){
  list<string> ans;
  for(Board* n: _mostStepsBoards)
    ans.push_back(to_string(n->id()) + ": " + to_string(n->stepsLeft()));
  return ans;
}
