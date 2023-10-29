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

  if(file.peek() == 'e')
    _goalId = -1;
  else{
    getline(file, line);
    _goalId = stoi(line);
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
    cout << "Tested " << testId << " / " << _boards.size() << " (" << _boards.size() - testId << ")" << endl;
    //testId = (int)_boards.size(); //DEBUG LINE TO ONLY GENERATE A FEW BOARDS
  }
  calculateMovePoints();
}

void BoardCollection::setStepsLeft(){
  if(_goal == nullptr){
    cout << "Error: goal not set" << endl;
    return;
  }
  list<Board*>* toBeCalculated;
  list<Board*>* beingCalculated;
  list<Board*>* temp;
  beingCalculated = new list<Board*>;
  toBeCalculated = new list<Board*>;
  for(Board* b: _boards){
    if(b->matchGoal(_goal))
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
  cout << "Steps left calculated" << endl;
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
  if(_goal != nullptr)
    ans.append(to_string(_goal->id()) + "\n");
  ans.append("e\n");
  return ans;
}

void BoardCollection::free(){
  for(Board* b: _boards){
    b->free();
    delete b;
  }
}

void BoardCollection::goal(Board* g){
  if(_goal != nullptr){
    for(Board* b: _boards){
      b->stepsLeft(-1);
    }
  }
  _goal = g;
  setStepsLeft();
  calculateBoardLists();
}

void BoardCollection::connectNeighbours(){
  for(Board* b: _boards)
    b->connectNeighbours(_boards);
}

void BoardCollection::addBoard(Board* board){
  _boards.push_back(board);
}

void BoardCollection::connectGoal(vector<Board*>& boards){
  if(_goalId < 0)
    return;
  int boardId = 0;
  bool foundGoal = false;
  while(boardId < (int)boards.size() && !foundGoal){
    if(boards[boardId]->id() == _goalId){
      foundGoal = true;
      _goal = boards[boardId];
    }
    boardId++;
  }
}

void BoardCollection::calculateMovePoints(){
  for(Board* b: _boards)
    b->calculateMovePoints();
}

void BoardCollection::calculateBoardLists(){
  cout << "calculateBoardLists" << endl;
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
  _goalBoards.resize(goalCount);
  _mostStepsBoards.resize(biggestCount);
  int goalId = 0;
  int biggestId = 0;
  for(Board* b: _boards){
    if(b->stepsLeft() == 0){
      _goalBoards[goalId++] = b;
    }else if(b->stepsLeft() == biggestStepsLeft){
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
