#include "Day04.h"

Day04::Day04()
{
  //ctor
}

Day04::~Day04()
{
  //dtor
}

void Day04::part1(string filename){
  InputLoader loader(filename);
  vector<vector<int>> elfPairs = loader.toVectorInt2d({"-", ","});
  int count = 0;
  for(vector<int> pair: elfPairs){
    if((pair[0] <= pair[2] && pair[1] >= pair[3]) ||
       (pair[2] <= pair[0] && pair[3] >= pair[1]))
      count++;
  }
  cout << "part 1: " << count << endl;
}

void Day04::part2(string filename){
  InputLoader loader(filename);
  vector<vector<int>> elfPairs = loader.toVectorInt2d({"-", ","});
  int count = 0;
  for(vector<int> pair: elfPairs){
    if((pair[2] >= pair[0] && pair[2] <= pair[1]) ||
       (pair[3] >= pair[0] && pair[3] <= pair[1]) ||
       (pair[2] < pair[0] && pair[3] > pair[1]))
      count++;
  }
  cout << "part 2: " << count << endl;
}
