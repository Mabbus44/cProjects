#ifndef RAIL_H
#define RAIL_H

#include <tuple>
#include <vector>
#include "RailNode.h"
#include "Util.h"

using namespace std;

enum Setup {ONETHREE, ONETWO, TWOTWO};

class RailNode;

class Rail
{
  public:
    Rail();
    Rail(Setup s);
    Rail(string c);
    virtual ~Rail();
    Rail(const Rail& r) {/*cout << "Rail copy" << endl;*/_nodes = r._nodes; _setup=r._setup;}
    void loadConfiguration(string c);
    void output();
    bool operator==(Rail& r);
    void swapNodes(Rail& r);
    void swapRailIds(int r1, int r2);
    void swapNodeIds(int rId, int n1, int n2);
    void invertNodes();
    int nodeCount();
    string toString();
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

