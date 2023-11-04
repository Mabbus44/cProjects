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

    Board* board(int i) {if((int)_boards.size() > i) {return _boards[i];} else {return nullptr;}}
    Board* goalBoard(int i) {if((int)_goalBoards.size() > i) {return _goalBoards[i];} else {return nullptr;}}
    Board* mostStepsBoard(int i) {if((int)_mostStepsBoards.size() > i) {return _mostStepsBoards[i];} else {return nullptr;}}
    int boardCount() {return _boards.size();}
    list<string> goalDescriptionList();
    list<string> mostDescriptionList();
    list<string> startDescriptionList();
    string getSaveString();
    void addBoard(Board* board);
    void calculateBoardLists();
    void calculateMovePoints();
    void connectNeighbours();
    void free();
    void generateChildren();
    void goal(Board* goal);
    void output(string tab = "");
    void setStepsLeft(Board* goal);
    void setStartingBoard(Board* startingBoard);

  protected:

  private:
    vector<Board*> _goalBoards;
    vector<Board*> _mostStepsBoards;
    vector<Board*> _boards;
};

#endif // BOARDCOLLECTION_H
