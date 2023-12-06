#include "Day06.h"

Day06::Day06()
{
  //ctor
}

Day06::~Day06()
{
  //dtor
}

void Day06::part1(string filename){
  InputLoader loader(filename);
  cout << "part 1: " << endl;
}

void Day06::part2(string filename){
  InputLoader loader(filename);
  __int64 time = 42686985;
  __int64 dist = 284100511221341;
  __int64 last = time/2;
  __int64 findFirst = 0;
  __int64 delta = last;
  bool add = true;
  bool isRecord = false;
  bool lastWasRecord = false;
  while(delta > 1 || !(isRecord && !lastWasRecord)){
    delta = delta/2;
    if(delta == 0)
      delta = 1;
    if(add)
      findFirst += delta;
    else
      findFirst -= delta;
    lastWasRecord = isRecord;
    isRecord = findFirst * (time-findFirst) > dist;
    add = !isRecord;
  }
  __int64 ans = (last-findFirst+1)*2;
  cout << "part 2: " << ans << endl;
}
