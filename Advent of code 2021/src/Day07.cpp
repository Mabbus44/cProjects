#include "Day07.h"

Day07::Day07()
{
  //ctor
}

Day07::~Day07()
{
  //dtor
}

void Day07::part1(string filename){
  InputLoader loader(filename);
  vector<vector<int>> input2d = loader.toVectorInt2d({","});
  vector<int> crabs = input2d[0];
  int pos = avg(crabs);
  int d = dist(crabs, pos);
  int dm1 = dist(crabs, pos-1);
  int dp1 = dist(crabs, pos+1);
  while(dm1<d || dp1<d){
    if(dm1<d){
      pos--;
      dp1=d;
      d=dm1;
      dm1=dist(crabs, pos-1);
    }else if(dp1>d){
      pos++;
      dm1=d;
      d=dp1;
      dp1=dist(crabs, pos+1);
    }
  }
  cout << "Part 1: " << d << endl;
}

void Day07::part2(string filename){
  InputLoader loader(filename);
  fuelConsumtion[0] = 0;
  for(int i=1; i<2000; i++)
    fuelConsumtion[i] = fuelConsumtion[i-1] +i;
  vector<vector<int>> input2d = loader.toVectorInt2d({","});
  vector<int> crabs = input2d[0];
  int pos = avg(crabs);
  int d = dist(crabs, pos, true);
  int dm1 = dist(crabs, pos-1, true);
  int dp1 = dist(crabs, pos+1, true);
  while(dm1<d || dp1<d){
    if(dm1<d){
      pos--;
      dp1=d;
      d=dm1;
      dm1=dist(crabs, pos-1, true);
    }else if(dp1>d){
      pos++;
      dm1=d;
      d=dp1;
      dp1=dist(crabs, pos+1, true);
    }
  }
  cout << "Part 2: " << d << endl;
}

int Day07::dist(vector<int>& crabs, int pos, bool exponential){
  int distSum=0;
  for(int crab:crabs){
    if(exponential)
      distSum += fuelConsumtion[abs(crab-pos)];
    else
      distSum += abs(crab-pos);
  }
  return distSum;
}

int Day07::avg(vector<int>& crabs){
  int sum=0;
  for(int crab:crabs)
    sum+=crab;
  return sum/crabs.size();
}
