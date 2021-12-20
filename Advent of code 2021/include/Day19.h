#ifndef DAY19_H
#define DAY19_H
#include <iostream>
#include <vector>
#include "Common.h"

class MyCoord{
  public:
    MyCoord(){}
    MyCoord(int x,int y,int z){this->x=x; this->y=y; this->z=z;}
    MyCoord(const MyCoord& other){x=other.x; y=other.y; z=other.z;}
    bool operator==(const MyCoord& other){return (x==other.x && y==other.y && z==other.z);}
    MyCoord& operator=(const MyCoord& other){x=other.x; y=other.y; z=other.z; return *this;}
    MyCoord operator-(const MyCoord& other){return MyCoord(x-other.x, y-other.y, z-other.z);}
    MyCoord operator+(const MyCoord& other){return MyCoord(x+other.x, y+other.y, z+other.z);}
    virtual ~MyCoord(){}
    MyCoord rot(int rotation);
    void output();
    bool possibleMatch(const MyCoord& other);   //Checks if 2 vectors can be aligned
    bool match(const MyCoord& other);
    int getRot(const MyCoord& other);
    int getLen();
    int x,y,z;
};

class Scanner{
  public:
    Scanner(){myPos.x=0; myPos.y=0; myPos.z=0;}
    virtual ~Scanner(){}
    void output();
    void loadMyCoord(string line);
    void rotationSanityCheck();
    int compare(Scanner* other);
    vector<MyCoord> convertToBase(vector<MyCoord>& convCoords);
    int x,y,z;
    int id;
    Scanner* relativeTo = NULL;
    int rotationToRel;
    MyCoord distToRel;
    vector<MyCoord> coords;
    MyCoord myPos;
};

class Day19
{
  public:
    Day19();
    virtual ~Day19();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY19_H
