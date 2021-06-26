#ifndef BTREE_H
#define BTREE_H
#define LEFT -1
#define NOROT 0
#define RIGHT 1
#include <iostream>

using namespace std;


class Leaf
{
  public:
    __int64 value;
    Leaf* left;
    Leaf* right;
    Leaf();
    Leaf(__int64 value);
    ~Leaf();
    void insert(__int64 value);
    Leaf* search(__int64 value);
    bool search(__int64 minVal, __int64 maxVal);
    void print();
    void printWeight(int level);
    void printChildren();
    int getHeight();
    Leaf* rotLeft();
    Leaf* rotRight();
    void balance();

  protected:

  private:
};

class Btree
{
  public:
    Btree();
    Btree(__int64 value);
    ~Btree();
    void insert(__int64 value);
    Leaf* search(__int64 value);
    bool search(__int64 minVal, __int64 maxVal);
    void print();
    void printWeight();
    void printChildren();
    void balance();

  protected:

  private:
    Leaf* root;
};

#endif // BTREE_H
