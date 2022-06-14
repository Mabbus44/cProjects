#include "Day23.h"
#include <list>

Day23::Day23()
{
  //ctor
}

Day23::~Day23()
{
  //dtor
}

void Day23::part1(string filename){
  list<int> cups = {1,5,8,9,3,7,4,6,2};
  list<int>::iterator currentCup = cups.begin();
  list<int>::iterator destCup;
  list<int>::iterator selectedCups[3];
  for(int rounds=0; rounds<100; rounds++){
    for(int i=0; i<3; i++){
      if(i==0)
        selectedCups[i] = currentCup;
      else
        selectedCups[i] = selectedCups[i-1];
      selectedCups[i]++;
      if(selectedCups[i] == cups.end())
        selectedCups[i] = cups.begin();
    }
    int destVal = *currentCup - 1;
    while(destVal < 1 ||
          destVal == *(selectedCups[0]) ||
          destVal == *(selectedCups[1]) ||
          destVal == *(selectedCups[2])){
      destVal--;
      if(destVal < 1)
        destVal = 9;
    }
    for(list<int>::iterator it=cups.begin(); it!=cups.end(); it++)
      if(*it == destVal)
        destCup = it;
    destCup++;
    cups.splice(destCup, cups, selectedCups[0]);
    cups.splice(destCup, cups, selectedCups[1]);
    cups.splice(destCup, cups, selectedCups[2]);
    currentCup++;
    if(currentCup == cups.end())
      currentCup = cups.begin();
  }
  while(*(cups.begin()) != 1)
    cups.splice(cups.end(), cups, cups.begin());
  cout << "part 1: ";
  for(list<int>::iterator it=cups.begin(); it!=cups.end(); it++)
    if(*it != 1)
      cout << *it;
  cout << endl;
}

void Day23::part2(string filename){
  vector<int> cupsInts = {1,5,8,9,3,7,4,6,2};
  Cup* firstCup = new Cup(cupsInts[0]);             //Create cup 1
  Cup* currentCup = firstCup;
  Cup* lastCup;
  Cup* finalCup;
  Cup* cupOne;
  for(int i=1; i<(int)cupsInts.size(); i++){
    currentCup->cupAfter = new Cup(cupsInts[i]);    //cupAfter for cup 1-8
    currentCup = currentCup->cupAfter;              //Create cup 2-9
    if(cupsInts[i] == 9)
      lastCup = currentCup;                         //Save cup with number 9
  }
  for(int i=10; i<=1000000; i++){
    currentCup->cupAfter = new Cup(i);              //cupAfter for cup 9-9 999 999
    currentCup = currentCup->cupAfter;              //create cup 10-10 000 000
    currentCup->numberBefore = lastCup;             //numberBefore for cup 10-10 000 000
    lastCup = currentCup;                           //Save cup with last number
  }
  currentCup->cupAfter = firstCup;                  //cupAfter for cup 10 000 000
  finalCup = currentCup;
  currentCup = firstCup;
  for(int i=0; i<(int)cupsInts.size(); i++){             //Go through first 9 cups
    if(currentCup->number == 1){
      currentCup->numberBefore = finalCup;          //numberBefore for cup with number 1
      cupOne = currentCup;
    }
    else{
      int targetNumber = currentCup->number - 1;
      Cup* currentCup2 = firstCup;
      for(int i2=0; i2<(int)cupsInts.size(); i2++){
        if(currentCup2->number == targetNumber)
          currentCup->numberBefore = currentCup2;   //numberBefore for cup with number 2-9
        currentCup2 = currentCup2->cupAfter;
      }
    }
    currentCup = currentCup->cupAfter;
  }

  currentCup = firstCup;
  for(int rounds=0; rounds<10000000; rounds++){
    Cup* destCup = currentCup->numberBefore;        //Take cup before
    while(destCup == currentCup->cupAfter || destCup == currentCup->cupAfter->cupAfter || destCup == currentCup->cupAfter->cupAfter->cupAfter)
      destCup = destCup->numberBefore;              //Make sure its not being moved
    Cup* afterDestcup = destCup->cupAfter;
    Cup* afterMovedCups = currentCup->cupAfter->cupAfter->cupAfter->cupAfter;
    destCup->cupAfter = currentCup->cupAfter;       //Move first number
    currentCup->cupAfter->cupAfter->cupAfter->cupAfter = afterDestcup;   //Move last number
    currentCup->cupAfter = afterMovedCups;         //Fill hole after currentCup
    currentCup = currentCup->cupAfter;
  }
  __int64 a = cupOne->cupAfter->number;
  __int64 b = cupOne->cupAfter->cupAfter->number;
  cout << "part 2: " << a*b;
  cout << endl;
}
