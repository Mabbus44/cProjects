#ifndef BOARDCOLLECTION_H
#define BOARDCOLLECTION_H

#include <vector>
#include "Board.h"

class BoardCollection
{
  public:
    BoardCollection();
    BoardCollection(ifstream& file);
    virtual ~BoardCollection();
    void setStartingBoard(Board* startingBoard);
    void generateChildren();
    void setStepsLeft();
    void output(string tab = "");
    string getSaveString();
    void free();
    void goal(Board* g);
    Board* board(int i) {if((int)_boards.size() > i) {return _boards[i];} else {return nullptr;}}
    Board* goalBoard(int i) {if((int)_goalBoards.size() > i) {return _goalBoards[i];} else {return nullptr;}}
    Board* mostStepsBoard(int i) {if((int)_mostStepsBoards.size() > i) {return _mostStepsBoards[i];} else {return nullptr;}}
    void connectNeighbours();
    void addBoard(Board* board);
    void connectGoal(vector<Board*>& boards);
    void calculateMovePoints();
    void calculateBoardLists();
    list<string> startDescriptionList();
    list<string> goalDescriptionList();
    list<string> mostDescriptionList();


  protected:

  private:
    vector<Board*> _boards;
    vector<Board*> _goalBoards;
    vector<Board*> _mostStepsBoards;
    Board* _goal = nullptr;
    int _goalId;
};

#endif // BOARDCOLLECTION_H
