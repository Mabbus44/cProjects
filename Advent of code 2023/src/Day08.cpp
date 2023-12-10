#include "Day08.h"

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
  vector<string> input = loader.toVectorStr();
  DirList dirs(input[0]);
  vector<MapNode*> nodes;
  for(int i=1; i<(int)input.size(); i++){
    if(input[i] != "")
      nodes.push_back(new MapNode(input[i]));
  }
  MapNode* location = nullptr;
  for(MapNode* n: nodes){
    n->setReferences(nodes);
    if(n->name() == "AAA")
      location = n;
  }
  while(!location->isGoal()){
    location = location->getNextNode(dirs.getDir());
  }
  cout << "part 1: " << dirs.steps() << endl;
}

void Day08::part2(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.toVectorStr();
  DirList dirs(input[0]);
  vector<MapNode*> nodes;
  for(int i=1; i<(int)input.size(); i++){
    if(input[i] != "")
      nodes.push_back(new MapNode(input[i]));
  }
  vector<MapNode*> startLocations;
  for(MapNode* n: nodes){
    n->setReferences(nodes);
    if(n->name()[2] == 'A')
      startLocations.push_back(n);
  }
  vector<Cycle> cycles;
  for(MapNode* n: startLocations){
    cycles.push_back(Cycle());
    cycles.back().calculateCycle(n, nodes, dirs);
  }

  PrimeFactorizer pf;
  vector<int> allFactors;
  for(Cycle& c: cycles){
    c.loopFactors = pf.factorize(c.loopSize);
    cout << c.loopSize << ": ";
    for(int f: c.loopFactors){
      cout << f << " ";
      //None of the cycles has multiple identical factors
      if(find(allFactors.begin(), allFactors.end(), f) == allFactors.end())
        allFactors.push_back(f);
    }
    cout << endl;

  }
  __int64 sum = 1;
  for(__int64 i: allFactors){
    sum *= i;
  }

  cout << "part 2: " << sum << endl;
}

void DirList::load(string input){
  for(char c: input){
    if(c == 'L')
      _list.push_back(Direction::left);
    if(c == 'R')
      _list.push_back(Direction::right);
  }
  _pos = 0;
}

Direction DirList::getDir(){
  Direction ret = _list[_pos];
  _pos++;
  _steps++;
  if(_pos >= (int)_list.size())
    _pos = 0;
  return ret;
}

void MapNode::load(string input){
  vector<string> parts = InputLoader::splitString(input, {" = (", ", ", ")"});
  _name = parts[0];
  _leftNodeString = parts[1];
  _rightNodeString = parts[2];
}

MapNode* MapNode::getNextNode(Direction dir){
  if(dir == Direction::left)
    return _leftNode;
  if(dir == Direction::right)
    return _rightNode;
  return nullptr;
}

bool MapNode::compare(MapNode& other){
  return _name == other._name;
}

void MapNode::setReferences(vector<MapNode*>& nodes){
  for(MapNode* n: nodes){
    if(n->_name == _leftNodeString)
      _leftNode = n;
    if(n->_name == _rightNodeString)
      _rightNode = n;
    if(_leftNode && _rightNode)
      return;
  }
}

void Cycle::calculateCycle(MapNode* startNode, vector<MapNode*>& nodeList, DirList& dirList){
  this->startNode = startNode;
  MapNode* location = startNode;
  dirList.reset();
  loopStartId = -1;
  addPosPlusNode(PosPlusNode{dirList.pos(), location});

  while(loopStartId == -1){
    location = location->getNextNode(dirList.getDir());
    if(location->isGoal02()){
      goalId = dirList.steps();
    }
    addPosPlusNode(PosPlusNode{dirList.pos(), location});
  }
  cycleSum = goalId;
  cout << "Start: " << startNode->name() << endl;
  cout << "LoopStart: " << loopStartId << endl;
  cout << "LoopSize: " << loopSize << endl;
  cout << "GoalIds: " << goalId << endl;
}

void Cycle::addPosPlusNode(PosPlusNode newPosPlusNode){
  for(int i=0; i<(int)posPlusNodes.size(); i++){
    if(posPlusNodes[i].pos == newPosPlusNode.pos && posPlusNodes[i].node == newPosPlusNode.node){
      loopStartId = i;
      loopSize = posPlusNodes.size() - i;
      return;
    }
  }
  posPlusNodes.push_back(newPosPlusNode);
}
