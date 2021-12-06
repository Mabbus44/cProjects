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
  vector<vector<int>> vvi = loader.toVectorInt2d({","});
  vector<int> fishes = vvi[0];
  for(int day=0; day<80; day++){
    int newFishes = 0;
    for(int fishId=0; fishId<(int)fishes.size(); fishId++){
      fishes[fishId]--;
      if(fishes[fishId]==-1){
        fishes[fishId]=6;
        newFishes++;
      }
    }
    for(int i=0; i<newFishes; i++)
      fishes.push_back(8);
  }
  cout << "Part 1: " << fishes.size() << endl;
}

void Day06::part2(string filename){
  InputLoader loader(filename);
  vector<vector<int>> vvi = loader.toVectorInt2d({","});
  vector<int> fishes = vvi[0];
  int64_t offsprings[6];
  for(int startDays=1; startDays<=5; startDays++){
    offsprings[startDays] = countOffspring(256, startDays+1);
    cout << startDays << ": " << offsprings[startDays] << endl;
  }
  int64_t fishCount=0;
  for(int fish: fishes){
    fishCount += (offsprings[fish]+1);
  }
  cout << "Part 2: " << fishCount << endl;
}

int64_t Day06::countOffspring(int days, int ageLeft){
  days-=ageLeft;
  if(days<0)
    return 0;
  int64_t offspring = countOffspring(days, 9)+1;
  for(int day=days-7;day>=0; day-=7)
    offspring+=(countOffspring(day, 9)+1);
  return offspring;
}
