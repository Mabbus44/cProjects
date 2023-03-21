#ifndef RAIL_H
#define RAIL_H

#include <vector>
#include "RailNode.h"
using namespace std;

enum Setup {ONETHREE, ONETWO, TWOTWO};

class RailNode;

class Rail
{
  public:
    Rail();
    Rail(Setup s);
    virtual ~Rail();
    Rail(const Rail& r) {_nodes = r._nodes;}
    void output();
    bool equivalent(Rail& r);
    void swapNodes(Rail& r);
    //set
    void nodes(vector<RailNode>& v){_nodes = v;}
    //get
    vector<RailNode>& nodes(){return _nodes;}
    Setup setup(){return _setup;}

  protected:

  private:
    vector<RailNode> _nodes;
    Setup _setup;
};

#endif // RAIL_H

