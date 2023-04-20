#include "RailWay.h"
#include <iostream>
#include <fstream>
#include <algorithm>

RailWay::RailWay()
{
  _connectedNodeCount = 0;
  _nodeCount = 0;
}

RailWay::RailWay(string c)
{
  _connectedNodeCount = 0;
  _nodeCount = 0;
  loadConfiguration(c);
}

RailWay::~RailWay()
{
}

void RailWay::addRail(Rail r)
{
  _rails.push_back(r);
  _nodeCount += r.nodeCount();
}

void RailWay::loadConfiguration(string c){
  c.erase(0,1);
  c.pop_back();
  vector<string> vs = splitString(c, {"] - ["});
  _connectedNodeCount = 0;
  _nodeCount = 0;
  for(auto s: vs){
    Rail r(s);
    _rails.push_back(r);
    _nodeCount += r.nodeCount();
  }
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
  int oldNodeCount = 0;

  cout << "Generating all configurations" << endl;
  while(it != children.end()){
    if(!(**it).done()){
      list<RailWay*> newChildren = (**it).getAllChildren(true);
      if(oldNodeCount != (**it).connectedNodeCount()){
        oldNodeCount = (**it).connectedNodeCount();
        outputWithDecimals(children.size());
        cout << " : " << (**it).connectedNodeCount() << "/" << (**it).nodeCount() << endl;
      }
      for(RailWay* newChild : newChildren){
        children.push_back(newChild);
      }
      children.erase(it++);
    }
    else{
      it = children.end();
    }
  }

  removeDuplicates(children);
  saveRailWays(children, "c:/temp/output.txt");
  cout << "Done" << endl;
}

void RailWay::removeDuplicates(list<RailWay*>& children){
  cout << "Removing duplicates" << endl;
  list<RailWay*>::iterator childIt = children.begin();
  int itNum = 0;

  while(childIt != children.end()){
    (*childIt)->removeIdenticalButSwappedRails(children, childIt, _swaps);
    childIt++;
    itNum++;
    outputWithDecimals(itNum);
    cout << "/";
    outputWithDecimals(children.size());
    cout << /*" (" << matchId << ")" << */endl;
  }
}

bool RailWay::operator==(RailWay& r){
  if(_rails.size() != r.rails().size()){
    cout << "WARNING: testing railways of different sizes" << endl;
    return false;
  }
  for(int i=0; i<(int)_rails.size(); i++){
    if(!(_rails[i] == r.rails()[i]))
      return false;
  }
  return true;
}

void RailWay::buildSwaps(){
  // This wont work if there is more then one invertable rail (like TWOTWO)
  _swaps.clear();
  map<Setup, vector<int>> setups;
  int railId=0;
  for(Rail& r: _rails){
    if(r.setup() == TWOTWO){
      _swaps.push_back({make_tuple(railId, railId)});
    }
    else if(setups.find(r.setup()) == setups.end()){
      setups.insert({r.setup(), {railId}});
    }else{
      setups[r.setup()].push_back(railId);
    }
    railId++;
  }
  for(auto m: setups){
    _swaps.push_back(getAllSwaps(m.second));
  }
  for(auto& s: _swaps){
    s.insert(s.begin(), make_tuple(-1, -1));
  }
}

void RailWay::removeIdenticalButSwappedRails(list<RailWay*>& children, list<RailWay*>::iterator testedRail, vector<list<tuple<int, int>>>& swaps){
  // This wont work if there is more then one invertable rail (like TWOTWO)
  vector<list<tuple<int, int>>::iterator> swapStatus(swaps.size());
  int sId = 0;
  for(auto& s: swaps){
    swapStatus[sId] = s.begin();
    sId++;
  }
  bool done = false;
  sId = 0;
  while(!done){
    if(swapStatus[sId] == swaps[sId].end()){
      swapStatus[sId] = swaps[sId].begin();
      sId++;
      if(sId >= (int)swaps.size())
        done = true;
      else{
        //Change back pos x before increasing
        swapRails(get<0>(*(swapStatus[sId])),get<1>(*(swapStatus[sId])));
        swapStatus[sId]++;
      }
    }else{
      //Change pos x
      swapRails(get<0>(*(swapStatus[sId])),get<1>(*(swapStatus[sId])));
      int childCount = 0;
      list<RailWay*>::iterator compareChild=testedRail;
      compareChild++;
      while(compareChild!=children.end()){
        if((*this) == (**compareChild)){
          children.erase(compareChild++);
        }else{
          compareChild++;
        }
        childCount++;
      }
      sId = 0;
      swapRails(get<0>(*(swapStatus[sId])),get<1>(*(swapStatus[sId])));
      swapStatus[sId]++;
    }
  }
}

list<tuple<int, int>> RailWay::getAllSwaps(vector<int>& railIds){
  list<tuple<int, int>> ret;
  for(int id1=0; id1<(int)railIds.size(); id1++){
    for(int id2=id1+1; id2<(int)railIds.size(); id2++){
      ret.push_back(make_tuple(railIds[id1], railIds[id2]));
    }
  }
  return ret;
}

void RailWay::swapRails(int railId1, int railId2){
  if(railId1==-1 || railId2==-1)
    return;
  if(railId1==railId2){
    _rails[railId1].invertNodes();
    for(auto &rail: _rails){
      for(auto &node: rail.nodes()){
        node.swapNodeIds(railId1, 0, 1);
      }
    }
  }
  else{
    _rails[railId1].swapNodes(_rails[railId2]);
    for(auto &rail: _rails){
      for(auto &node: rail.nodes()){
        node.swapRailIds(railId1, railId2);
      }
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
      int toRailId = railId;
      int toNodeId = nodeId;
      if(_rails[railId].nodes()[nodeId].hasTwoFree()){
        RailWay* newChild = new RailWay(*this);
        newChild->connectToNextFree(railId, nodeId, toRailId, toNodeId);
        newChild->setChildrenStart(railId, nodeId);
        ret.push_back(newChild);
      }
      while(toRailId != -1){
        RailWay* newChild = new RailWay(*this);
        tie(toRailId, toNodeId) = newChild->connectToNextFree(railId, nodeId, toRailId, toNodeId+1);
        if(toRailId == -1){
          delete newChild;
        }
        else{
          newChild->setChildrenStart(railId, nodeId);
          ret.push_back(newChild);
        }
      }
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
  _connectedNodeCount += 2;
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
      if(!_rails[railId].nodes()[nodeId].full())
        return make_tuple(railId, nodeId);
    }
  }
  return make_tuple(-1, -1);
}

void RailWay::outputWithDecimals(int n){
  __int64 factor = 1000;
  while(n/factor > 0){
    factor *= 1000;
  }
  factor /= 1000;
  while(factor>1){
    cout << n/factor << ",";
    n = n - (n/factor) * factor;
    factor /= 1000;
  }
  cout << n;
}

string RailWay::toString(){
  string ans = "";
  bool first = true;
  for(auto& r: _rails){
    if(!first)
      ans += " - ";
    first = false;
    ans += ("[" + r.toString() + "]");
  }
  return ans;
}

void RailWay::connectRails(vector<vector<int>> rawRail){
  for(int i=0; i<(int)rawRail.size(); i++){
    _rails[rawRail[i][0]].nodes()[rawRail[i][1]].connect(rawRail[i][2], rawRail[i][3]);
    _rails[rawRail[i][2]].nodes()[rawRail[i][3]].connect(rawRail[i][0], rawRail[i][1]);
  }

  _connectedNodeCount = rawRail.size() * 2;
}

void RailWay::saveRailWays(list<RailWay*>& railWays, string fileName){
  ofstream myfile (fileName);
  for(auto& rail: railWays){
    myfile << (*rail).toString() << endl;
  }
  myfile.close();
}

void RailWay::loadRailWays(list<RailWay*>& railWays, string fileName){
  ifstream myfile (fileName);
  string line;
  while(getline(myfile, line)){
    railWays.push_back(new RailWay(line));
  }
  myfile.close();
}

bool RailWay::addNodeToPaths(map<string, vector<tuple<int, int>>>& paths, int railId, int nodeId){
  bool added = false;
  tuple<int, int> railNode = make_tuple(railId, nodeId);
  for(auto& path:  paths){
    if(find(path.second.begin(), path.second.end(), railNode) == path.second.end()){
      added = true;
      path.second.push_back(railNode);
    }
  }
  return added;
}

void RailWay::findPath(map<string, vector<tuple<int, int>>>& paths, int railId, int nodeId){
  bool foundNew = false;
  string id = to_string(railId) + to_string(nodeId);
  if(paths.find(id) == paths.end()){
    paths.insert(pair<string, vector<tuple<int, int>>>(id, new vector<tuple<int, int>>));
  }
  _rails[railId].getNodes()[1-nodeId];
}
