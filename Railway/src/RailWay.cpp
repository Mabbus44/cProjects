#include "RailWay.h"
#include <iostream>

RailWay::RailWay()
{
  //ctor
}

RailWay::~RailWay()
{
  //dtor
}

void RailWay::addRail(Rail r)
{
  _rails.push_back(r);
}

void RailWay::output(){
  cout << "OUTPUT" << endl;
  int i = 0;
  for(Rail& r: _rails){
    cout << " Rail " << i << endl;
    r.output();
    i++;
  }
}

void RailWay::getAllConfigurations(){
  list<RailWay*> children = getAllChildren(true);
  list<RailWay*>::iterator it = children.begin();
  while(it != children.end()){
    list<RailWay*> newChildren = (**it).getAllChildren(true);
    for(RailWay* c : newChildren){
      children.push_back(c);
    }
    it++;
    __int64 cSize = (int)children.size();
    __int64 factor = 1000;
    while(cSize/factor > 0){
      factor *= 1000;
    }
    factor /= 1000;
    while(factor>1){
      cout << cSize/factor << ",";
      cSize = cSize - (cSize/factor) * factor;
      factor /= 1000;
    }
    cout << cSize << endl;
  }
  //cout << children.size() << endl;
}

bool RailWay::equivalent(RailWay& r){
  if(_rails.size() != r.rails().size()){
    cout << "WARNING: testing railways of different sizes" << endl;
    return false;
  }
  for(int i=0; i<(int)_rails.size(); i++){
    if(!_rails[i].equivalent(r.rails()[i]))
      return false;
  }
  return true;
}

bool RailWay::identicalButSwappedRails(RailWay& r){
  map<Setup, vector<int>> setups;
  for(Rail& r: _rails){
    if(setups.find(r.setup()) == setups.end()){

    }
  }
}

list<RailWay*> RailWay::getAllChildren(bool onlyFromOneNode){
  list<RailWay*> ret;
  int railId=_startGeneratingChildrenFromRail;
  int nodeId=_startGeneratingChildrenFromNode;
  while(railId != -1){
    tie(railId, nodeId) = getNextFree(railId, nodeId);
    if(railId != -1){
      cout << "Connecting (" << railId << ", " << nodeId << ")" << endl;
      int toRailId = railId;
      int toNodeId = nodeId;
      while(toRailId != -1){
        RailWay* newChild = new RailWay(*this);
        tie(toRailId, toNodeId) = newChild->connectToNextFree(railId, nodeId, toRailId, toNodeId+1);
        if(toRailId == -1){
          delete newChild;
          //cout << "  done" << endl;
        }
        else{
          //cout << "  to (" << toRailId << ", " << toNodeId << ")" << endl;
          newChild->setChildrenStart(railId, nodeId+1);
          ret.push_back(newChild);
        }
      }
    }
    else{
      //cout << "DONE" << endl;
    }
    nodeId++;
    if(onlyFromOneNode)
      railId = -1;
  }
  return ret;
}

tuple<int, int> RailWay::connectToNextFree(int fromRail, int fromNode, int toRail, int toNode){
  tie(toRail, toNode) = getNextFree(toRail, toNode);
  if(toRail == -1)
    return make_tuple(-1, -1);
  _rails[fromRail].nodes()[fromNode].connect(toRail, toNode);
  _rails[toRail].nodes()[toNode].connect(fromRail, fromNode);
  return make_tuple(toRail, toNode);
}

tuple<int,int> RailWay::getNextFree(int startRailId, int startNodeId){
  bool first = true;
  for(int railId=startRailId; railId < (int)_rails.size(); railId++){
    int actualStartNodeId = 0;
    if(first)
      actualStartNodeId = startNodeId;
    first = false;
    for(int nodeId=actualStartNodeId; nodeId < (int)_rails[railId].nodes().size(); nodeId++){
      if(!_rails[railId].nodes()[nodeId].isConnected())
        return make_tuple(railId, nodeId);
    }
  }
  return make_tuple(-1, -1);
}
