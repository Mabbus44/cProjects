#ifndef DAY08_H
#define DAY08_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

enum Direction {left, right};

class DirList{
  public:
    DirList(){}
    DirList(string input) {load(input);}
    virtual ~DirList(){}
    void load(string input);
    Direction getDir();
    void reset() {_pos = 0; _steps = 0;}
    int steps() {return _steps;}
    int pos() {return _pos;}
  private:
    int _pos = 0;
    vector<Direction> _list;
    int _steps = 0;
};

class MapNode{
  public:
    MapNode(){}
    MapNode(string input){load(input);}
    virtual ~MapNode(){}
    void load(string input);
    MapNode* getNextNode(Direction dir);
    bool compare(MapNode& other);
    void setReferences(vector<MapNode*>& nodes);
    string name() {return _name;}
    bool isGoal() {return _name == "ZZZ";}
    bool isGoal02() {return _name[2] == 'Z';}
  private:
    string _name;
    MapNode* _leftNode = nullptr;
    MapNode* _rightNode = nullptr;
    string _leftNodeString;
    string _rightNodeString;
};

struct PosPlusNode{
  public:
    int pos;
    MapNode* node;
};

class Cycle{
  public:
    Cycle(){}
    virtual ~Cycle(){}
    void calculateCycle(MapNode* startNode, vector<MapNode*>& nodeList, DirList& dirList);
    void addPosPlusNode(PosPlusNode newPosPlusNode);
    MapNode* startNode;
    vector<PosPlusNode> posPlusNodes;
    int loopStartId = -1;
    int loopSize = -1; //Loopsize and goalId happends to be identical, which simplfies things
    int goalId; //There is only one goal in each loop, I tested
    int cycleSum = 0;
    vector<int> loopFactors;
};

class Day08
{
  public:
    Day08();
    virtual ~Day08();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY08_H
