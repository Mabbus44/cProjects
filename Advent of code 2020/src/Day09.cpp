#include "Day09.h"

Day09::Day09()
{
  //ctor
}

Day09::~Day09()
{
  //dtor
}

void Day09::part1(string filename){
  InputLoader loader(filename);
  vector<int64_t> input = loader.toBigInt(loader.toVectorStr());
  int ans=0;
  bool totalyDone=false;
  for(int i=25; i<(int)input.size() && !totalyDone; i++){
    int done=false;
    for(int a=1; a<26 && !done; a++){
      for(int b=a+1; b<26 && !done; b++){
        if(a!=b){
          if(input[i-a]+input[i-b]==input[i])
            done = true;
        }
      }
    }
    if(!done){
      ans=input[i];
      totalyDone = true;
    }
  }
  totalyDone = false;
  int ans2;
  for(int i=0; i<(int)input.size() && !totalyDone; i++){
    int64_t sum = input[i];
    int i2=i;
    while(sum<ans){
      i2++;
      sum+=input[i2];
    }
    if(sum==ans){
      totalyDone = true;
      int64_t minI=9999999999999;
      int64_t maxI=0;
      for(int i3=i; i3<=i2; i3++){
        if(input[i3]<minI)
          minI = input[i3];
        if(input[i3]>maxI)
          maxI = input[i3];
      }
      ans2 = minI+maxI;
    }
  }
  cout << "part 1: " << ans << endl;
  cout << "part 2: " << ans2 << endl;
}

void Day09::part2(string filename){
}
