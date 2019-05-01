#ifndef GUARD_H
#define GUARD_H

#include <iostream>
#include <list>
#include "Event.h"

using namespace std;

class Guard
{
  public:
    Guard();
    Guard(int id);
    virtual ~Guard();
    void calcTime();
    void output();
    int id;
    list<Event> eventList;
    int totalTime;
    int bestMinute;
    int bestMinuteCount;

  protected:

  private:
};

#endif // GUARD_H
