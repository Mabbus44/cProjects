#include "RailNode.h"
#include <iostream>

RailNode::RailNode()
{
  //ctor
}

RailNode::RailNode(vector<int> intCon){
  _internalConnections = intCon;
}

RailNode::~RailNode()
{
  //dtor
}

void RailNode::output(){
  cout << _externalConnectionRail << "," << _externalConnectionNode << " ";
  bool writeComma = false;
  for(int i: _internalConnections){
    if(writeComma)
      cout << ",";
    cout << i;
    writeComma = true;
  }
  cout << endl;
}

bool RailNode::equivalent(RailNode& n){
  if(_internalConnections.size() != n.internalConnections().size())
    return false;
  for(int i=0; i<(int)_internalConnections.size(); i++){
    if(_internalConnections[i] != n.internalConnections()[i])
      return false;
  }
  if(_externalConnectionRail != -1 && n.externalConnectionRail() != -1 && _externalConnectionRail != n.externalConnectionRail())
    return false;
  if(_externalConnectionNode != -1 && n.externalConnectionNode() != -1 && _externalConnectionNode != n.externalConnectionNode())
    return false;
  return true;
}
