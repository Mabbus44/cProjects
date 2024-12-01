#include "Day01.h"

Day01::Day01()
{
  //ctor
}

Day01::~Day01()
{
  //dtor
}

void Day01::part1(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<int>> input = loader.toVectorInt2d({"   "});
  std::vector<int> listA;
  std::vector<int> listB;
  for(std::vector<int> row: input){
    listA.push_back(row[0]);
    listB.push_back(row[1]);
  }
  std::sort(listA.begin(), listA.end());
  std::sort(listB.begin(), listB.end());
  int totDiff = 0;
  for(int i=0; i<(int)listA.size(); i++){
    totDiff += (std::abs(listA[i]-listB[i]));
  }
  std::cout << "part 1: " << totDiff << std::endl;
}

void Day01::part2(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<int>> input = loader.toVectorInt2d({"   "});
  std::vector<int> listA;
  std::vector<int> listB;
  for(std::vector<int> row: input){
    listA.push_back(row[0]);
    listB.push_back(row[1]);
  }
  std::sort(listA.begin(), listA.end());
  std::sort(listB.begin(), listB.end());
  int score = 0;
  int idA=0;
  int idB=0;
  while(idA<(int)listA.size() && idB<(int)listB.size()){
    while(idA<(int)listA.size() && idB<(int)listB.size() && listA[idA] < listB[idB]){
      idA++;
    }
    while(idA<(int)listA.size() && idB<(int)listB.size() && listA[idA] > listB[idB]){
      idB++;
    }
    int matchCount = 0;
    int num = 0;
    int idBStart = idB;
    while(idA<(int)listA.size() && idB<(int)listB.size() && listA[idA] == listB[idB]){
      matchCount++;
      num = listA[idA];
      idB++;
    }
    if(matchCount > 0){
      score += (matchCount*num);
      idA++;
      idB = idBStart;
    }
  }
  std::cout << "part 2: " << score << std::endl;
}
