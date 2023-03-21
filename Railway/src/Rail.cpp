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
    _nodes.push_back(RailNode({1, 2}));
    _nodes.push_back(RailNode({0}));
    _nodes.push_back(RailNode({0}));
  }else if(s == ONETHREE){
    _nodes.push_back(RailNode({1, 2, 3}));
    _nodes.push_back(RailNode({0}));
    _nodes.push_back(RailNode({0}));
    _nodes.push_back(RailNode({0}));
  }else if(s == TWOTWO){
    _nodes.push_back(RailNode({2, 3}));
    _nodes.push_back(RailNode({2, 3}));
    _nodes.push_back(RailNode({0, 1}));
    _nodes.push_back(RailNode({0, 1}));
  }else{
    cout << "ERROR: Invalid setup for rail" << endl;
  }
}

Rail::~Rail()
{
  //dtor
}

void Rail::output(){
  int i=0;
  for(RailNode& n: _nodes){
    cout << "  " << i << ": ";
    n.output();
    i++;
  }
}

bool Rail::equivalent(Rail& r){
  if(r.nodes().size() != _nodes.size())
    return false;
  for(int i=0; i<(int)_nodes.size(); i++){
    if(!_nodes[i].equivalent(r.nodes()[i]))
      return false;
  }
  return true;
}

void Rail::swapNodes(Rail& r){
  vector<RailNode> temp = _nodes;
  _nodes = r.nodes();
  r.nodes(temp);
}
