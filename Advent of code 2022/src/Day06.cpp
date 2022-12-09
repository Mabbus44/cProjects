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
  string dataStream = loader.toVectorStr()[0];
  int stepsUntilUniqe = 0;
  int ans;
  for(int i=0; i<dataStream.size(); i++){
    for(int i2=1; i2<4; i2++){
      if(i-i2>=0 && dataStream[i] == dataStream[i-i2]){
        stepsUntilUniqe = max(4-i2, stepsUntilUniqe);
      }
    }
    stepsUntilUniqe--;
    if(i>2 && stepsUntilUniqe == -1){
      ans = i+1;
      break;
    }
  }

  cout << "part 1: " << ans << endl;
}

void Day06::part2(string filename){
  InputLoader loader(filename);
  string dataStream = loader.toVectorStr()[0];
  int stepsUntilUniqe = 0;
  int ans;
  for(int i=0; i<dataStream.size(); i++){
    for(int i2=1; i2<14; i2++){
      if(i-i2>=0 && dataStream[i] == dataStream[i-i2]){
        stepsUntilUniqe = max(14-i2, stepsUntilUniqe);
      }
    }
    stepsUntilUniqe--;
    if(i>12 && stepsUntilUniqe == -1){
      ans = i+1;
      break;
    }
  }

  cout << "part 2: " << ans << endl;
}
