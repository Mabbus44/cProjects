#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <iostream>
#include "Functions.h"

#define WAKES_UP -1
#define FALLS_ASLEEP -2

using namespace std;

class Event
{
  public:
    Event();
    Event(string line);
    virtual ~Event();
    bool operator<(const Event& other);
    void load(string line);
    void output();
    int year, month, day, hour, minute;
    int event;

  protected:

  private:
};

#endif // EVENT_H
