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
  r.getAllConfigurations();
  return 0;
}
