#include "Guard.h"

Guard::Guard()
{
  //ctor
}

Guard::Guard(int id)
{
  this->id = id;
}

Guard::~Guard()
{
  //dtor
}

void Guard::calcTime()
{
  int beginTime;
  bool beginRead = false;
  int minutes[60];
  bestMinuteCount = 0;
  for(int i=0; i<60; i++)
    minutes[i] = 0;
  totalTime = 0;
  bestMinute = 0;
  for(list<Event>::iterator it = eventList.begin(); it != eventList.end(); ++it)
  {
    if(!beginRead)
    {
      beginTime = it->minute;
      beginRead = true;
    }
    else
    {
      totalTime += it->minute - beginTime;
      for(int i=beginTime; i<it->minute; i++)
        minutes[i]++;
      beginRead = false;
    }
  }
  for(int i=0; i<60; i++)
  {
    if(minutes[i]>bestMinuteCount)
    {
      bestMinute = i;
      bestMinuteCount = minutes[i];
    }
  }
}

void Guard::output()
{
  cout << "Guard ID: " << id << endl;
  cout << "Total time: " << totalTime << endl;
  cout << "Best minute: " << bestMinute << endl;
  for(list<Event>::iterator it = eventList.begin(); it != eventList.end(); ++it)
    it->output();
}
