#ifndef RAILNODE_H
#define RAILNODE_H

#include <vector>
#include "Rail.h"
using namespace std;

class Rail;

class RailNode
{
  public:
    RailNode();
    RailNode(vector<int> intCon);
    virtual ~RailNode();
    RailNode(const RailNode& n) {_internalConnections = n._internalConnections;}
    void output();
    bool equivalent(RailNode& n);
    bool isConnected() {return _externalConnectionRail != -1;}
    void connect(int r, int n) {_externalConnectionRail = r; _externalConnectionNode = n;}
    //set
    void internalConnections(vector<int>& v){_internalConnections = v;}
    void externalConnectionRail(int v){_externalConnectionRail = v;}
    void externalConnectionNode(int v){_externalConnectionNode = v;}
    //get
    vector<int>& internalConnections(){return _internalConnections;}
    int externalConnectionRail(){return _externalConnectionRail;}
    int externalConnectionNode(){return _externalConnectionNode;}

  protected:

  private:
    vector<int> _internalConnections;
    int _externalConnectionRail = -1;
    int _externalConnectionNode = -1;
};

#endif // RAILNODE_H
