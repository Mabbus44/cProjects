#include "Event.h"

Event::Event()
{
  //ctor
}

Event::Event(string line)
{
  load(line);
}

Event::~Event()
{
  //dtor
}

bool Event::operator<(const Event& other)
{
  if(year<other.year)
    return true;
  if(year>other.year)
    return false;
  if(month<other.month)
    return true;
  if(month>other.month)
    return false;
  if(day<other.day)
    return true;
  if(day>other.day)
    return false;
  if(hour<other.hour)
    return true;
  if(hour>other.hour)
    return false;
  if(minute<other.minute)
    return true;
  if(minute>other.minute)
    return false;
  return false;
}

void Event::load(string line)
{
  unsigned int index = 0;
  string wakes = "wakes up";
  string falls = "falls asleep";
  year = nextNumber(line, index, true);
  month = nextNumber(line, index);
  day = nextNumber(line, index);
  hour = nextNumber(line, index);
  minute = nextNumber(line, index);
  if(line.find(wakes) != string::npos)
    event = WAKES_UP;
  else if(line.find(falls) != string::npos)
    event = FALLS_ASLEEP;
  else
    event = nextNumber(line, index);
}

void Event::output()
{
  cout << year << "-" << month << "-" << day << " " << hour << ":" << minute << " ";
  if(event == WAKES_UP)
    cout << "wakes up";
  if(event == FALLS_ASLEEP)
    cout << "falls asleep";
  if(event >= 0)
    cout << "guard #" << event << " begins shift";
  cout << endl;
}
