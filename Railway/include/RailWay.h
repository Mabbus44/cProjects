#ifndef RAILWAY_H
#define RAILWAY_H

#include <tuple>
#include <vector>
#include <list>
#include <map>
#include "Rail.h"
using namespace std;

class RailWay
{
  public:
    RailWay();
    virtual ~RailWay();
    RailWay(const RailWay& r) {_rails = r._rails;}
    void addRail(Rail r);
    void output();
    void getAllConfigurations();
    bool equivalent(RailWay& r);
    list<RailWay*> getAllChildren(bool onlyFromOneNode);
    tuple<int, int> connectToNextFree(int fromRail, int fromNode, int toRail, int toNode);
    tuple<int, int> getNextFree(int startRailId, int startNodeId);
    void setChildrenStart(int r, int n) {_startGeneratingChildrenFromRail = r; _startGeneratingChildrenFromNode = n;}
    bool identicalButSwappedRails(RailWay& r);

    //set
    void rails(vector<Rail>& v){_rails = v;}
    //get
    vector<Rail>& rails(){return _rails;}

  protected:

  private:
    vector<Rail> _rails;
    int _startGeneratingChildrenFromRail = 0;
    int _startGeneratingChildrenFromNode = 0;
};

#endif // RAILWAY_H
