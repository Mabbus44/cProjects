#ifndef DAY07_H
#define DAY07_H
#include <iostream>
#include <list>
#include "Common.h"

using namespace std;

const string DAY07_DISKPOS = "DiskPos";
const string DAY07_FILE = "File";
const string DAY07_FOLDER = "Folder";

class Day07
{
  public:
    Day07();
    virtual ~Day07();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

class DiskPos
{
  public:
    DiskPos(){};
    DiskPos(DiskPos* parent, string name){this->parent = parent; this->name = name;}
    virtual ~DiskPos(){}
    virtual __int64 diskSize(){return _diskSize;}
    virtual void output(string tab){}
    virtual string getType() {return DAY07_DISKPOS;}
    string name;
    DiskPos* parent = nullptr;
  protected:
    __int64 _diskSize;
};

class File: public DiskPos
{
  public:
    File(){};
    File(DiskPos* parent, __int64 diskSize, string name):DiskPos(parent, name){_diskSize = diskSize;}
    void output(string tab) {cout << tab << name << ": " << _diskSize << endl;}
    virtual string getType() {return DAY07_FILE;}
    virtual ~File(){};
};

class Folder: public DiskPos
{
  public:
    Folder(){_diskSize = -1;}
    Folder(DiskPos* parent, string name):DiskPos(parent, name){_diskSize = -1;}
    bool addChild(string input);
    void output(string tab);
    Folder* cd(string dirName);
    __int64 diskSize();
    virtual string getType() {return DAY07_FOLDER;}
    __int64 sumAllFoldersLessThan(__int64 maxVal);
    __int64 biggestValSmallerThan(__int64 minVal, __int64 bestMatch);
    virtual ~Folder(){};
    list<DiskPos*> children;
};
#endif // DAY07_H
