#include "RailNode.h"
#include <bits/stdc++.h>
#include <iostream>

RailNode::RailNode()
{
  //ctor
}

RailNode::RailNode(int maxCon){
  _maxConnections = maxCon;
}

RailNode::~RailNode()
{
  //dtor
}

void RailNode::loadConfiguration(string c){
  c.erase(0,1);
  c.pop_back();
  vector<string> vs = splitString(c, {"),("});
  _maxConnections = vs.size();
  for(auto s: vs){
    vector<string> vs = splitString(s, {","});
    _connections.push_back(make_tuple(stoi(vs[0]), stoi(vs[1])));
  }
}

void RailNode::output(){
  bool writeComma = false;
  for(tuple<int, int>& t: _connections){
    if(writeComma)
      cout << ",";
    cout << "{" << get<0>(t)<< ", " << get<1>(t) << "}";
    writeComma = true;
  }
  cout << endl;
}

bool RailNode::operator==(RailNode& n){
  if(_connections.size() != n.connections().size())
    return false;
  for(int i=0; i<(int)_connections.size(); i++){
    bool found = false;
    for(int i2=0; !found && i2<(int)_connections.size(); i2++){
      if(_connections[i] == n.connections()[i2])
        found = true;
    }
    if(!found)
      return false;
  }
  return true;
}

bool RailNode::connect(int r, int n){
  if(full())
    return false;
  _connections.push_back(make_tuple(r, n));
  return true;
}

string RailNode::toString(){
  string ans = "";
  bool first = true;
  for(auto& n: _connections){
    if(!first)
      ans += ",";
    first = false;
    ans += ("(" + to_string(get<0>(n)) + "," + to_string(get<1>(n)) + ")");
  }
  return ans;
}

void RailNode::swapRailIds(int r1, int r2){
  for(auto &connection: _connections){
    if(get<0>(connection) == r1)
      get<0>(connection) = r2;
    else if(get<0>(connection) == r2)
      get<0>(connection) = r1;
  }
}

void RailNode::swapNodeIds(int rId, int n1, int n2){
  for(auto &connection: _connections){
    if(get<0>(connection) == rId){
      if(get<1>(connection) == n1)
        get<1>(connection) = n2;
      else if(get<1>(connection) == n2)
        get<1>(connection) = n1;
    }
  }
}
