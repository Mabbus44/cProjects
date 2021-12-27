#ifndef DAY22_H
#define DAY22_H
#include <iostream>
#include <vector>
#include "Common.h"

class Cube{
public:
  Cube(){}
  Cube(int ix1,int ix2,int iy1,int iy2,int iz1,int iz2,bool ion, bool output=false, string tab=""){x1=ix1;y1=iy1;z1=iz1;x2=ix2;y2=iy2;z2=iz2;on=ion;if(output)this->output(tab, true);}
  Cube(const Cube& c){x1=c.x1;y1=c.y1;z1=c.z1;x2=c.x2;y2=c.y2;z2=c.z2;on=c.on;children=c.children;}
  virtual ~Cube(){}
  Cube& operator=(const Cube& c){x1=c.x1;y1=c.y1;z1=c.z1;x2=c.x2;y2=c.y2;z2=c.z2;on=c.on;children=c.children; return *this;}
  void load(vector<int>& inst, bool output=false, string tab="");
  void output(string tab, bool oneLine=false);
  int64_t getOnCubes(int ix1,int ix2,int iy1,int iy2,int iz1,int iz2);
  void free();
  void merge();
  int64_t countCubes();
  vector<Cube*> children;
  bool on=false;
  int x1,y1,z1,x2,y2,z2;
};

class Day22
{
  public:
    Day22();
    virtual ~Day22();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY22_H
