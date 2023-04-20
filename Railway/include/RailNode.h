#ifndef RAILNODE_H
#define RAILNODE_H

#include <tuple>
#include <vector>
#include <iostream>
#include "Rail.h"
#include "Util.h"

using namespace std;

class Rail;

class RailNode
{
  public:
    RailNode();
    RailNode(int maxCon);
    RailNode(string c){loadConfiguration(c);}
    virtual ~RailNode();
    RailNode(const RailNode& n) {_maxConnections = n._maxConnections; _connections = n._connections;/*cout << "RailNode copy " << toString() << endl;*/}
    void loadConfiguration(string c);
    void output();
    bool operator==(RailNode& n);
    bool full() {return _maxConnections <= (int)_connections.size();}
    bool hasTwoFree() {return _maxConnections-2 >= (int)_connections.size();}
    bool connect(int r, int n);
    string toString();
    void swapRailIds(int r1, int r2);
    void swapNodeIds(int rId, int n1, int n2);
    //set
    void connections(vector<tuple<int, int>>& v){_connections = v;}
    void maxConnections(int v){_maxConnections = v;}
    //get
    vector<tuple<int, int>>& connections(){return _connections;}
    int maxConnections(){return _maxConnections;}

  protected:

  private:
    int _maxConnections;
    vector<tuple<int, int>> _connections;
};

#endif // RAILNODE_H
