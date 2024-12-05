#include "Day05.h"

Day05::Day05()
{
  //ctor
}

Day05::~Day05()
{
  //dtor
}

void Day05::part1(std::string filename){
  InputLoader loader1(filename+"-1.txt");
  rules = loader1.toVectorInt2d({"|"});
  InputLoader loader2(filename+"-2.txt");
  updates = loader2.toVectorInt2d({","});
  int sum = 0;
  for(std::vector<int> update: updates){
    if(followsRules(update)){
      sum += middleValue(update);
    }
  }
  std::cout << "part 1: " << sum << std::endl;
}

void Day05::part2(std::string filename){
  InputLoader loader1(filename+"-1.txt");
  rules = loader1.toVectorInt2d({"|"});
  InputLoader loader2(filename+"-2.txt");
  updates = loader2.toVectorInt2d({","});
  int sum = 0;
  for(std::vector<int> update: updates){
    if(!followsRules(update)){
      orderUpdate(update);
      sum += middleValue(update);
    }
  }
  std::cout << "part 2: " << sum << std::endl;
}

bool Day05::followsRules(std::vector<int>& update){
  int id1, id2;
  for(std::vector<int> rule: rules){
    id1 = -1;
    id2 = -1;
    for(int i=0; i<(int)update.size(); i++){
      if(update[i] == rule[0])
        id1 = i;
      if(update[i] == rule[1])
        id2 = i;
    }
    if(id1 == -1|| id2 == -1)
      continue;
    else
      if(id2 <= id1)
        return false;
  }
  return true;
}

int Day05::middleValue(std::vector<int>& update){
  int pos = (update.size()+1)/2-1;
  return update[pos];
}

void Day05::orderUpdate(std::vector<int>& update){
  for(int uId=0; uId<(int)update.size(); uId++){
    int backUidTo = -1;
    for(int rId=0; backUidTo == -1 && rId < (int)rules.size(); rId++){
      std::vector<int> rule = rules[rId];
      int findId = -1;
      if(update[uId] == rule[0])
        findId = 1;
      if(update[uId] == rule[1])
        findId = 0;
      if(findId>-1){
        for(int uId2=0; backUidTo == -1 && uId2<(int)update.size(); uId2++){
          if(uId != uId2 && update[uId2]== rule[findId] && ((findId == 0 && uId2 > uId) || (findId == 1 && uId2 < uId))){
            std::swap(update[uId], update[uId2]);
            backUidTo = std::min(uId, uId2);
          }
        }
      }
    }
    if(backUidTo > -1)
      uId = backUidTo-1;
  }
}
