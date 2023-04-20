#ifndef RAILWAY_H
#define RAILWAY_H

#include <tuple>
#include <vector>
#include <list>
#include <map>
#include "Rail.h"
#include "Util.h"
using namespace std;

class RailWay
{
  public:
    RailWay();
    RailWay(string c);
    virtual ~RailWay();
    RailWay(const RailWay& r) {/*cout << "RailWay copy" << endl;*/_rails = r._rails; _nodeCount = r._nodeCount; _connectedNodeCount = r._connectedNodeCount;}
    void addRail(Rail r);
    void loadConfiguration(string c);
    void output();
    void getAllConfigurations();
    void removeDuplicates(list<RailWay*>& children);
    bool operator==(RailWay& r);
    list<RailWay*> getAllChildren(bool onlyFromOneNode);
    tuple<int, int> connectToNextFree(int fromRail, int fromNode, int toRail, int toNode);
    tuple<int, int> getNextFree(int startRailId, int startNodeId);
    void setChildrenStart(int r, int n) {_startGeneratingChildrenFromRail = r; _startGeneratingChildrenFromNode = n;}
    void removeIdenticalButSwappedRails(list<RailWay*>& children, list<RailWay*>::iterator testedRail, vector<list<tuple<int, int>>>& swaps);
    void outputWithDecimals(int n);
    list<tuple<int, int>> getAllSwaps(vector<int>& railIds);
    void swapRails(int railId1, int railId2);
    void buildSwaps();
    bool done() {return _connectedNodeCount >= _nodeCount;}
    void connectRails(vector<vector<int>> rawRail);
    void saveRailWays(list<RailWay*>& railWays, string fileName);
    void loadRailWays(list<RailWay*>& railWays, string fileName);
    void findPath(map<string, vector<tuple<int, int>>>& paths, int railId, int nodeId);
    bool addNodeToPaths(map<string, vector<tuple<int, int>>>& paths, int railId, int nodeId);

    //set
    void rails(vector<Rail>& v){_rails = v;}
    //get
    vector<Rail>& rails(){return _rails;}
    int nodeCount(){return _nodeCount;}
    int connectedNodeCount(){return _connectedNodeCount;}
    string toString();

  protected:

  private:
    vector<Rail> _rails;
    int _startGeneratingChildrenFromRail = 0;
    int _startGeneratingChildrenFromNode = 0;
    vector<list<tuple<int, int>>> _swaps;
    int _nodeCount;
    int _connectedNodeCount;
};

#endif // RAILWAY_H
