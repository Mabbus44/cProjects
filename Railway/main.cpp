#include <iostream>
#include "RailWay.h"
using namespace std;

int main()
{
  RailWay r;
  r.addRail(ONETWO);
  r.addRail(ONETWO);
  r.addRail(ONETHREE);
  r.addRail(ONETHREE);
  r.addRail(TWOTWO);
  r.buildSwaps();
  //r.getAllConfigurations();
  list<RailWay*> railWays;
  cout << "Loading...";
  r.loadRailWays(railWays, "c:/temp/no loops.txt");
  cout << "done" << endl;
  //r.removeDuplicates(railWays);
  //r.removeLoops(railWays);
  r.selectBest(railWays);
  cout << "Saving " << railWays.size() << " railways...";
  r.saveRailWays(railWays, "c:/temp/best of no loops.txt");
  cout << "done" << endl;
  return 0;
}
