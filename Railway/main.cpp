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
  r.loadRailWays(railWays, "c:/temp/17000 uniqe rails.txt");
  cout << "done" << endl;
  /*r.removeDuplicates(railWays);
  int i=0;
  for(auto railWay: railWays){
    i++;
    cout << railWay->toString() << endl;
  }*/
  cout << railWays.size() << endl;
  return 0;
}
