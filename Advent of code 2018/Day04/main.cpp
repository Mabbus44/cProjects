#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Event.h"
#include "Guard.h"

using namespace std;

int main()
{
  ifstream input;
  string line;
  list<string> inputList;
  list<Event> eventList;
  list<Guard> guardList;
  Guard* activeGuard;
  int bestGuardSleepTime = 0;
  int bestGuardID = 0;
  int bestGuardBestMinute = 0;
  int bestGuard2SleepCount = 0;
  int bestGuard2ID = 0;
  int bestGuard2BestMinute = 0;

  input.open("C:\\Users\\rasun\\Documents\\C++ Projects\\Advent of code 2018\\Input\\Day04.txt");
  while(getline(input, line))
  {
    inputList.push_back(line);
    Event newEvent(line);
    eventList.push_back(line);
  }
  input.close();
  eventList.sort();
  for(list<Event>::iterator it = eventList.begin(); it != eventList.end(); ++it)
  {
    if(it->event >= 0)
    {
      bool newGuard = true;
      for(list<Guard>::iterator it2 = guardList.begin(); it2 != guardList.end(); ++it2)
      {
        if(it2->id == it->event)
        {
          activeGuard = &(*it2);
          newGuard = false;
        }
      }
      if(newGuard)
      {
        Guard g(it->event);
        guardList.push_front(g);
        activeGuard = &(*(guardList.begin()));
      }
    }
    else
      activeGuard->eventList.push_back(*it);
  }
  for(list<Guard>::iterator it = guardList.begin(); it != guardList.end(); ++it)
  {
    it->calcTime();
    if(it->totalTime > bestGuardSleepTime)
    {
      bestGuardID = it->id;
      bestGuardSleepTime = it->totalTime;
      bestGuardBestMinute = it->bestMinute;
    }
    if(it->bestMinuteCount > bestGuard2SleepCount)
    {
      bestGuard2ID = it->id;
      bestGuard2SleepCount = it->bestMinuteCount;
      bestGuard2BestMinute = it->bestMinute;
    }
  }
  cout << "Part 1: " << bestGuardID << " * " << bestGuardBestMinute << " = " << bestGuardID*bestGuardBestMinute << endl;;
  cout << "Part 2: " << bestGuard2ID << " * " << bestGuard2BestMinute << " = " << bestGuard2ID*bestGuard2BestMinute << " (sleepcout " << bestGuard2SleepCount << ")";
  return 0;
}
