#include "Rail.h"
#include <iostream>

Rail::Rail()
{
  //ctor
}

Rail::Rail(Setup s)
{
  _setup = s;
  if(s == ONETWO)
  {
    _nodes.push_back(RailNode(1));
    _nodes.push_back(RailNode(2));
  }else if(s == ONETHREE){
    _nodes.push_back(RailNode(1));
    _nodes.push_back(RailNode(3));
  }else if(s == TWOTWO){
    _nodes.push_back(RailNode(2));
    _nodes.push_back(RailNode(2));
  }else{
    cout << "ERROR: Invalid setup for rail" << endl;
  }
}

Rail::Rail(string c){
  loadConfiguration(c);
}

Rail::~Rail()
{
  //dtor
}

void Rail::loadConfiguration(string c){
  c.erase(0,1);
  c.pop_back();
  vector<string> vs = splitString(c, {"} {"});
  for(auto s: vs){
    RailNode n(s);
    _nodes.push_back(n);
  }
  if(_nodes[0].maxConnections() == 1 || _nodes[1].maxConnections() == 1){
    if(_nodes[0].maxConnections() == 2 || _nodes[1].maxConnections() == 2)
      _setup = ONETWO;
    else
      _setup = ONETHREE;
  }
    _setup = TWOTWO;
}

int Rail::nodeCount(){
  return _nodes[0].maxConnections() + _nodes[1].maxConnections();
}

void Rail::output(){
  int i=0;
  for(RailNode& n: _nodes){
    cout << "  " << i << ": ";
    n.output();
    i++;
  }
}

bool Rail::operator==(Rail& r){
  if(r.nodes().size() != _nodes.size())
    return false;
  for(int i=0; i<(int)_nodes.size(); i++){
    if(!(_nodes[i]==(r.nodes()[i])))
      return false;
  }
  return true;
}

void Rail::swapNodes(Rail& r){
  vector<RailNode> temp = _nodes;
  _nodes = r.nodes();
  r.nodes(temp);
}

void Rail::swapRailIds(int r1, int r2){
  for(auto &node: _nodes){
    node.swapRailIds(r1, r2);
  }
}

void Rail::swapNodeIds(int rId, int n1, int n2){
  for(auto &node: _nodes){
    node.swapNodeIds(rId, n1, n2);
  }
}

void Rail::invertNodes(){
  RailNode temp = _nodes[1];
  _nodes[1] = _nodes[0];
  _nodes[0] = temp;
}

string Rail::toString(){
  string ans = "";
  bool first = true;
  for(auto& n: _nodes){
    if(!first)
      ans += " ";
    first = false;
    ans += ("{" + n.toString() + "}");
  }
  return ans;
}
